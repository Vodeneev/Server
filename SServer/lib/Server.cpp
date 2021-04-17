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
	addr.sin_port = htons(1000);
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
	int size_msg = 0;
	recv(connection, (char*)&size_msg, sizeof(int), NULL);
	int error = WSAGetLastError();
	char* msg = new char[size_msg + 1];
	msg[size_msg] = '\0';
	recv(connection, msg, size_msg, NULL);
	mtx.lock();
	database.insert(Mymap::value_type(msg, connection));
	mtx.unlock();
	mtx.lock();
	std::cout << msg << std::endl;
	mtx.unlock();
	delete msg;
}

void Server::Write_in_file(std::string path)
{
	std::ofstream out;
	out.open(path);
	if (out.is_open())
	{
		for(auto it = database.begin(); it != database.end(); it++)
			out << it->first << std::endl;
	}
	out.close();
}

void Server::SetStartStop()
{
	read.lock();
	write.lock();
	start_stop = false;
	write.unlock();
	read.unlock();
}

void Server::StopWork()
{
	SetStartStop();
	closesocket(slisten);
}


bool Server::GetStartStop()
{
	write.lock();
	bool res = start_stop;
	write.unlock();
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
		if (GetStartStop() != true)
			break;
		Threads.push_back(std::thread(&Server::Recv, this, newConnection));
	}

	for (int i = 0; i < Threads.size(); i++)
	{
		Threads[i].join();
	}
}
