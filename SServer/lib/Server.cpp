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

void Server::Recv(char msg[BYTE_N], SOCKET connection)
{
	recv(connection, msg, sizeof(msg), NULL);
	std::cout << msg << std::endl;
}

int Server::Counter()
{
	return counter;
}

