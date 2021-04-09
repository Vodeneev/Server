#include "Client.h"

int main()
{
	Client cl;
	cl.Connect();
	char msg[256];
	cl.Recv(msg);
}
