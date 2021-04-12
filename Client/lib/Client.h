#pragma once
#pragma comment(lib, "ws2_32.lib")
#include <iostream>
#include<WinSock2.h>
#define BYTE_N 256
#include <string>

#pragma warning(disable: 4996)


class Client
{
	WSAData wsaData;
	SOCKADDR_IN addr;
	SOCKET connection;
public:
	Client();
	void SetAddr(int port);
	void Connect();
	void Send(std::string msg);
};

