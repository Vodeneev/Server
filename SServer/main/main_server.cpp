#include"Server.h"
#include<functional>


int main()
{
	Server S;
	std::string end_word = " ";
	std::mutex mtx;

	S.Connect();

	std::thread l(&Server::StartWork, std::ref(S));

	while (end_word != "stop")
	{
		std::cout << "Enter the 'stop' command to finish the operation : ";
		std::cin >> end_word;
		if (end_word != "stop")
			std::cout << "Incorrect stop word" << std::endl;
	}

	S.StopWork();

	l.join();

	return 0;
}
