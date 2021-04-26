#include "CLient.h"

Client::Client()
{
	WORD DLLVersion = MAKEWORD(2, 2);
	if (WSAStartup(DLLVersion, &wsaData) != 0)
	{
		std::cout << "Error connecting the library" << std::endl;
		exit(1);
	}
	addr.sin_addr.s_addr = inet_addr("127.0.0.1"); // all local host adresses
	addr.sin_port = htons(1000);
	addr.sin_family = AF_INET; // internet protocol family
	connection = SOCKET();
}

void Client::SetAddr(int port)
{
	addr.sin_port = htons(port);
}

void Client::Connect()
{
	connection = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	connect(connection, (SOCKADDR*)&addr, sizeof(addr));
	
	std::cout << "Connected\n";

}

void Client::Send(ClientData* msg)
{
	char* m = msg->GetString();
	int size_msg = msg->Size();
	send(connection, (char*)&size_msg, sizeof(int), NULL);
	send(connection, m, size_msg, NULL);
}

