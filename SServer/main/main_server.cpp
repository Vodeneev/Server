#include"Server.h"
#include<functional>



int main()
{
	Server S;
	std::vector<std::thread> Threads;
	std::vector<SOCKET> connections;
	char Messages[N_CLIENTS][BYTE_N];

	while (true)
	{
		connections.push_back(S.Connect());
		Threads.push_back(std::thread(&Server::Recv, S, Messages[S.Counter() - 1], connections[S.Counter() - 1]));
	}

	for (int i = 0; i < Threads.size(); i++)
	{
		Threads[i].join();
	}
} 
