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
	
	start_stop = true;
}

void Server::SetAddr(int port)
{
	addr.sin_port = htons(port);
}

void Server::Connect()
{
	int sizeofaddr = sizeof(addr);
	bind(slisten, (SOCKADDR*)&addr, sizeof(addr)); //associates a local address with a socket
	listen(slisten, SOMAXCONN); // listening for an incoming connection
}

void Server::Send(char msg[BYTE_N], SOCKET connection)
{
	send(connection, msg, sizeof(msg), NULL);
}

void Server::Recv(SOCKET connection)
{
	size_t size_msg;
	recv(connection, (char*)&size_msg, sizeof(size_t), NULL);
	char* msg = new char[size_msg + (size_t)1];
	msg[size_msg] = '\0';
	recv(connection, msg, size_msg, NULL);
	mtx.lock();
	database[msg] = connection;
	mtx.unlock();
	mtx.lock();
	std::cout << msg << std::endl;
	mtx.unlock();
}

void Server::StopWork()
{
	start_stop = false;
	closesocket(slisten);
}

bool Server::GetStartStop()
{
	read.lock();
	bool res = start_stop;
	read.unlock();
	return res;
}

void Server::StartWork()
{
	std::vector<std::thread> Threads;
	SOCKET newConnection = 0;
	int sizeofaddr = sizeof(addr);

	while (true)
	{
		newConnection = accept(slisten, (SOCKADDR*)&addr, &sizeofaddr);
		if (start_stop != true)
			break;
		Threads.push_back(std::thread(&Server::Recv, this, newConnection));
	}

	for (int i = 0; i < Threads.size(); i++)
	{
		Threads[i].join();
	}
}
