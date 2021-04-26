#include"Server.h"
#include<functional>
#include<time.h>


int main()
{
	srand(time(NULL));
	Server S;
	std::string end_word = " ";
	std::mutex mtx;

	S.Connect();

	std::thread l(&Server::StartWork, std::ref(S));

	while (end_word != "stop")
	{
		std::cin >> end_word;
		if (end_word != "stop")
			std::cout << "Incorrect stop word" << std::endl;
	}

	S.StopWork();

	l.join();

	std::string path = "C:/Users/1/Desktop/ClientsID";
	S.Write_in_file(path);

	return 0;
}
