#pragma once
#pragma comment(lib, "ws2_32.lib")
#include <iostream>
#include <WinSock2.h>
#include <vector>
#include<thread>
#include<mutex>
#define BYTE_N 256
#define DATABASE_SIZE 2
#include <string>

#pragma warning(disable: 4996)

class Server
{
	WSAData wsaData;
	SOCKADDR_IN addr;
	SOCKET slisten;
	int counter;
	std::vector<std::string> Messages;
	std::mutex mtx;
public:
	Server();
	void SetAddr(int port);
	SOCKET Connect();
	void Send(char msg[BYTE_N], SOCKET connection);
	void Server::Recv(SOCKET connection);
	int Counter();
};

