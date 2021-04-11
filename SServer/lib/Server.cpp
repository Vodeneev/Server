#include "Server.h"

Server::Server()
{
	WORD DLLVersion = MAKEWORD(2, 2);
	if (WSAStartup(DLLVersion, &wsaData) != 0)
	{
		std::cout << "Error connecting the library" << std::endl;
		exit(1);
	}

	addr.sin_addr.s_addr = inet_addr("127.0.0.1");; //local host adresses
	addr.sin_port = htons(1111);
	addr.sin_family = AF_INET; // internet protocol family

	slisten = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	counter = 0;

	Messages.resize(DATABASE_SIZE);
}

void Server::SetAddr(int port)
{
	addr.sin_port = htons(port);
}

SOCKET Server::Connect()
{
	int sizeofaddr = sizeof(addr);
	bind(slisten, (SOCKADDR*)&addr, sizeof(addr)); //associates a local address with a socket
	listen(slisten, SOMAXCONN); // listening for an incoming connection
	SOCKET newConnection = 0;
	while (newConnection == 0)
	{
		newConnection = accept(slisten, (SOCKADDR*)&addr, &sizeofaddr);
	}
	counter++;
	return newConnection;
}

void Server::Send(char msg[BYTE_N], SOCKET connection)
{
	send(connection, msg, sizeof(msg), NULL);
}

void Server::Recv(SOCKET connection)
{
	mtx.lock();
	if (Messages.size() < counter)
	{
		std::vector<std::vector<char>> temp(counter, std::vector<char>(BYTE_N));
		for (int i = 0; i < counter - 1; i++)
			for (int j = 0; j < BYTE_N; j++)
				temp[i][j] = Messages[i][j];
		Messages.resize(counter + DATABASE_SIZE);
		for (int i = 0; i < counter - 1; i++)
		{
			Messages[i] = new char[BYTE_N];
			for (int j = 0; j < BYTE_N; j++)
				Messages[i][j] = temp[i][j];
		}
	}
	mtx.unlock();
	Messages[counter - 1] = new char[BYTE_N];
	recv(connection, Messages[counter - 1], sizeof(Messages[counter - 1]), NULL);
	std::cout << Messages[counter - 1] << std::endl;
}

int Server::Counter()
{
	return counter;
}

