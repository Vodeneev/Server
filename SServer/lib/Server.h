#pragma once
#pragma comment(lib, "ws2_32.lib")
#include <iostream>
#include <WinSock2.h>
#include <vector>
#include<thread>
#define BYTE_N 256
#define N_CLIENTS 2

#pragma warning(disable: 4996)

class Server
{
	WSAData wsaData;
	SOCKADDR_IN addr;
	SOCKET slisten;

public:
	Server();
	void SetAddr(int port);
	SOCKET Connect();
	void Send(char msg[BYTE_N], SOCKET connection);
	void Server::Recv(char msg[BYTE_N], SOCKET connection);
};

