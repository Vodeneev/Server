#include "Client.h"

int main()
{
	Client cl;
	cl.Connect();
	char msg[256] = "Hello 1";
	cl.Send(msg);
}
