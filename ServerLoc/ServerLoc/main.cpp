#include"Server.h"
#include<functional>
#include<time.h>


//int main()
//{
//	
//	std::string bufstr = "gg 6";
//	std::cout << bufstr << std::endl;
//
//	uLong comprLen = bufstr.size() + 13;
//	Byte* res = new Byte[comprLen];
//	int returnCode;
//	returnCode = compress(res, &comprLen, (const Byte*)bufstr.c_str(), bufstr.size()+1);
//
//	char* str = new char[comprLen + 1];
//	str[0] = 'b';
//	for (int i = 0; i < comprLen; i++)
//	{
//		str[i + 1] = res[i];
//	}
//	int size = _msize(str) / sizeof(char) - 1;
//	std::string strin(str);
//	Byte* res2 = new Byte[strin.size()];
//	for (int i = 0; i < strin.size(); i++)
//		res2[i] = strin[i + 1];
//
//	char buf[256];
//	uLong comprLen2 = 256;
//	returnCode = uncompress((Byte*)buf, &comprLen2, res2, strin.size());
//	std::cout << buf;
//	return 0;
//
//}

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
