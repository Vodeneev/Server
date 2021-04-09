#include"Server.h"


int main()
{
	Server S;
	SOCKET connection = S.Connect();
	char msg[256] = "Hello!";
	S.Send(msg, connection);
} 












//
//
//WSAData wsaData;
//WORD DLLVersion = MAKEWORD(2, 2);
//if (WSAStartup(DLLVersion, &wsaData) != 0)
//{
//	std::cout << "Error connecting the library" << std::endl;
//	exit(1);
//}
//
//SOCKADDR_IN addr; // socket's addres from Internet protocol
//addr.sin_addr.s_addr = inet_addr("127.0.0.1");; //local host adresses
//addr.sin_port = htons(1111);
//addr.sin_family = AF_INET; // internet protocol family
//int sizeofaddr = sizeof(addr);
//
//SOCKET slisten = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
//bind(slisten, (SOCKADDR*)&addr, sizeof(addr)); //associates a local address with a socket
//listen(slisten, SOMAXCONN); // listening for an incoming connection
//SOCKET newConnection;
//newConnection = accept(slisten, (SOCKADDR*)&addr, &sizeofaddr); // established a connection with the client
//if (newConnection == 0)
//{
//	std::cout << "Error connected" << std::endl;
//}
//else
//{
//	std::cout << "Client connected" << std::endl;
//	char msg[250] = "Hello!";
//	send(newConnection, msg, sizeof(msg), NULL);
//}
//
//system("pause");