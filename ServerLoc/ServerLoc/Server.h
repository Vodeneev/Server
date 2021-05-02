#pragma once
#pragma comment(lib, "ws2_32.lib")
#include <iostream>
#include <WinSock2.h>
#include <vector>
#include<thread>
#include<mutex>
#include <string>
#include <unordered_map>
#include<fstream>
#include"ClientData.h"

#define DATABASE_SIZE 10

#pragma warning(disable: 4996)

typedef std::unordered_map<SOCKET, ClientData> Mymap;


class Server
{
	WSAData wsaData;
	SOCKADDR_IN addr;
	SOCKET slisten;
	std::unordered_map<SOCKET, ClientData*> database;
	std::mutex mtx;
	std::mutex read;
	std::mutex write;
	bool start_stop;
public:
	Server();
	void SetAddr(int port);
	void Connect();
	void StartWork();
	void Recv(SOCKET connection);
	void Write_in_file(std::string path);
	void SetStartStop();
	void StopWork();
	bool GetStartStop();
};

