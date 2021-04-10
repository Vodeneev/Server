#include"Server.h"
#include<functional>



int main()
{
	Server S;
	std::vector<std::thread> Threads(N_CLIENTS);
	std::vector<SOCKET> connections(N_CLIENTS);
	char Messages[N_CLIENTS][BYTE_N];

	for (int i = 0; i < N_CLIENTS; i++)
	{
		connections[i] = S.Connect();
		Threads[i] = std::thread(&Server::Recv, S, Messages[i], connections[i]);
	}

	for (int i = 0; i < N_CLIENTS; i++)
	{
		Threads[i].join();
	}

	system("pause");
} 
