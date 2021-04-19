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

	while (connect(connection, (SOCKADDR*)&addr, sizeof(addr)) != 0)
	{

	}
	
	std::cout << "Connected\n";

}

void Client::Send(std::string msg)
{
	int size_msg = msg.size();
	send(connection, (char*)&size_msg, sizeof(int), NULL);
	send(connection, msg.c_str(), size_msg, NULL);
}

void Client::Send_zip(std::string msg, std::string path)
{
	std::ofstream file;
	file.open(path);
	if (file.is_open())
	{
		file << msg << std::endl;
	}
	file.close();

	std::string WinRAR_param = "\"C:/Program Files/WinRAR/WinRar.exe\" a -afzip -ep ";
	std::string path_zip = path + ".zip ";
	system((WinRAR_param + path_zip + path).c_str());

	int size_msg = path.size();
	send(connection, (char*)&size_msg, sizeof(int), NULL);
	send(connection, path.c_str(), size_msg, NULL);
}

