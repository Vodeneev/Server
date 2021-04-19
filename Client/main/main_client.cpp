#include "Client.h"
#include<time.h>

int main(int argc, char** argv)
{
	srand(time(NULL));
	Client cl;
	cl.Connect();
	int r = rand();
	if (argc == 1)
	{
		std::string msg = "Invalid_ID";
		cl.Send_zip(msg, "C:/Users/1/Desktop/Clients/" + std::to_string(r));
	}
	else
		cl.Send_zip(argv[1], "C:/Users/1/Desktop/Clients/" + std::to_string(r));
}
