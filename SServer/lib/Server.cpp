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
		std::vector<std::string> temp(counter);
		for (int i = 0; i < counter - 1; i++)
			temp[i] = Messages[i];

		Messages.resize(counter + (size_t)DATABASE_SIZE);

		for (int i = 0; i < counter - 1; i++)
			Messages[i] = temp[i];
	}
	mtx.unlock();
	size_t size_msg;
	recv(connection, (char*)&size_msg, sizeof(size_t), NULL);
	char* msg = new char[size_msg + (size_t)1];
	msg[size_msg] = '\0';
	recv(connection, msg, size_msg, NULL);
	Messages[counter - (size_t)1] = msg;
	mtx.lock();
	std::cout << Messages[counter - (size_t)1] << std::endl;
	mtx.unlock();
}

int Server::Counter()
{
	return counter;
}

