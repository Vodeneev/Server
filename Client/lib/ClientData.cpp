#include "ClientData.h"

Simple::Simple()
{
	data = {};
	size = 0;
	str = nullptr;
}

Simple::Simple(std::string a)
{
	data = new char[(a.size() + 2) * sizeof(char)];
	for (int i = 0; i < a.size(); i++)
	{
		data[i + 1] = a[i];
	}
	size = a.size() + 1;
	data[size] = '\0';
	data[0] = 'a';
	str = new char[sizeof(char) * (size + 1)];
	for (int i = 0; i < size; i++)
		str[i] = data[i];
	str[size] = '\0';
}

char* Simple::GetString()
{
	return str;
}



Zip::Zip()
{
	data = {};
	hash = 0;
	size = 0;
	str = nullptr;
}

Zip::Zip(std::string a, int hash, char type)
{
	data = new char[a.size() + 1];
	for (int i = 0; i < a.size(); i++)
	{
		data[i] = a[i];
	}
	size = a.size();
	data[size] = '\0';
	this->hash = hash;
	SetString(type);
}

void Zip::SetString(char type)
{
	std::string msg(data);
	if (type == 'b')
		msg += ' ' + std::to_string(hash);
	else
		msg = std::to_string(hash) + ' ' + msg;

	int r = rand();
	std::string path_file = "C:/Users/1/Desktop/Clients/" + std::to_string(r) + ".txt";
	std::string name_file = std::to_string(r) + ".txt ";
	std::ofstream file(path_file);
	if (file.is_open())
	{
		file << msg << std::endl;
	}
	file.close();

	std::string path_zip = "C:/Users/1/Desktop/Clients/" + std::to_string(r + 1) + ".zip";
	system(("\"7za.exe\"  a -tzip -mx=1 " + path_zip + " -y -r " + path_file).c_str());

	int length;
	char* buffer;

	std::ifstream is;
	is.open(path_zip, std::ios::binary);

	// get length of file:
	is.seekg(0, std::ios::end);
	length = is.tellg();
	is.seekg(0, std::ios::beg);

	// allocate memory:
	buffer = new char[length];

	// read data as a block:
	is.read(buffer, length);
	is.close();
	std::string res(buffer);
	str = new char[length + 2 + name_file.size()];
	for (int i = 0; i < length; i++)
	{
		str[i + 1 + name_file.size()] = buffer[i];
	}
	for (int i = 0; i < name_file.size(); i++)
	{
		str[i + 1] = name_file[i];
	}
	if (type == 'b')
		str[0] = 'b';
	else
		str[0] = 'c';
	size = length + 1 + name_file.size();
	str[size] = '\0';
	delete[] buffer;
}


