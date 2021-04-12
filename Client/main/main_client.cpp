#include "Client.h"

int main(int argc, char** argv)
{
	Client cl;
	cl.Connect();
	if (argc == 1)
	{
		std::string msg = "Invalid id";
		cl.Send(msg);
	}
	else
		cl.Send(argv[1]);
}
