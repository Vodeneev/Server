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
	addr.sin_port = htons(1111);
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

	if (connect(connection, (SOCKADDR*)&addr, sizeof(addr)) != 0)
	{
		std::cout << "Error connection from client" << std::endl;
	}
	else
	{
		std::cout << "Connected\n";
	}
}

void Client::Recv(char msg[BYTE_N])
{
	recv(connection, msg, sizeof(msg), NULL);
	std::cout << msg << std::endl;
}



