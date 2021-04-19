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
#define BYTE_N 256
#define DATABASE_SIZE 2
typedef std::unordered_map<std::string, SOCKET> Mymap;

#pragma warning(disable: 4996)

class Server
{
	WSAData wsaData;
	SOCKADDR_IN addr;
	SOCKET slisten;
	std::unordered_map<std::string, SOCKET> database;
	std::mutex mtx;
	std::mutex read;
	std::mutex write;
	bool start_stop;
public:
	Server();
	void SetAddr(int port);
	void Connect();
	void StartWork();
	void Send(char msg[BYTE_N], SOCKET connection);
	void Server::Recv(SOCKET connection);
	void Server::Recv_zip(SOCKET connection);
	void Server::Write_in_file(std::string path);
	void SetStartStop();
	void StopWork();
	bool Server::GetStartStop();
};

