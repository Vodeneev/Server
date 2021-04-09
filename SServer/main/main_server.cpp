#include"Server.h"


int main()
{
	Server S;
	SOCKET connection = S.Connect();
	char msg[256] = "Hello!";
	S.Send(msg, connection);
} 
