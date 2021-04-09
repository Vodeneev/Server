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
	SOCKET newConnection = accept(slisten, (SOCKADDR*)&addr, &sizeofaddr); // established a connection with the client
	if (newConnection == 0)
	{
		std::cout << "Error connected" << std::endl;
	}
	else
	{
		std::cout << "Connected from server" << std::endl;
	}
	return newConnection;
}

void Server::Send(char msg[BYTE_N], SOCKET connection)
{
	send(connection, msg, sizeof(msg), NULL);
}



