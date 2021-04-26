#include "Client.h"
#include<time.h>
#include<locale.h>

#define N_keys 100

int hash_function(std::string key)
{
	return std::stoi(key) % N_keys;
}

int HF(std::string key)
{
	int hashf = 0;

	int i = 0;
	while (i < key.size())
	{
		hashf += key[i];
		i++;
	}

	return hashf % N_keys;
}

int main(int argc, char** argv)
{
	setlocale(LC_ALL, "rus");
	srand(time(NULL));
	Client cl;
	cl.Connect();
	
	std::cout << "Введите сообщение: ";
	std::string msg;

	std::cin >> msg;
	std::cout << std::endl;

	std::cout << "Выберите вид отправки: " << std::endl << "1. Простое сообщение" << std::endl <<
		"2. Zip архив. Хэш-функция - сообщение" << std::endl << "3. Zip архив. Сообщение - хэш-функция" << std::endl << std::endl;

	int type;
	std::cin >> type;

	bool flag = true;
	while (flag)
	{
		switch (type)
		{
		case 1:
		{
			Simple message(msg);
			cl.Send(&message);
			flag = false;
		}
			break;
		case 2:
		{
			int hsh = HF(msg);
			Zip message(msg, hsh, 'b');
			cl.Send(&message);
			flag = false;
		}
			break;
		case 3:
		{
			int hsh = HF(msg);
			Zip message(msg, hsh, 'c');
			cl.Send(&message);
			flag = false;
		}
			break;
		default:
			std::cout << "Неизвестный тип" << std::endl;
			std::cin >> type;
			break;
		}
	}
}
