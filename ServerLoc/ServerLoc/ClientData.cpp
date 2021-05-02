#include "ClientData.h"

Simple::Simple()
{
	data = {};
	size = 0;
	file_str = nullptr;
}

Simple::Simple(char* a)
{
	size = _msize(a) / sizeof(char) - 1;
	data = new char[size + 1];
	for (int i = 0; i < size; i++)
		data[i] = a[i + 1];
	data[size] = '\0';
	file_str = nullptr;
	SetString();
}

void Simple::SetString()
{
	file_str = new char[size + 1];
	for (int i = 0; i < size; i++)
	{
		file_str[i] = data[i];
	}
	file_str[size] = '\0';
}



Zip::Zip()
{
	data = {};
	hash = 0;
	size = 0;
	file_str = nullptr;
}

Zip::Zip(char* a)
{
	std::string msg(a);
	data = new Byte[msg.size()];
	for (int i = 0; i < msg.size(); i++)
		data[i] = msg[i + 1];
	size = msg.size();
	file_str = nullptr;
	SetString();
}

void Zip::SetString()
{
	char buf[256];
	uLong comprLen = 256;
	int returnCode = uncompress((Byte*)buf, &comprLen, data, size);
	
	std::string str_buf(buf);
	char t = str_buf[str_buf.size() - 1];
	int i = str_buf.size() - 1;
	std::string hsh;
	while (t != ' ')
	{
		hsh.push_back(t);
		i--;
		t = str_buf[i];
	}
	std::reverse(hsh.begin(), hsh.end());
	hash = std::stoi(hsh);

	file_str = new char[str_buf.size() + 1];
	for (int i = 0; i < str_buf.size(); i++)
		file_str[i] = buf[i];
	file_str[str_buf.size()] = '\0';
}


Zip2::Zip2(char* a)
{
	std::string msg(a);
	data = new Byte[msg.size()];
	for (int i = 0; i < msg.size(); i++)
		data[i] = msg[i + 1];
	size = msg.size();
	file_str = nullptr;
	SetString();
}

void Zip2::SetString()
{
	char buf[256];
	uLong comprLen = 256;
	int returnCode = uncompress((Byte*)buf, &comprLen, data, size);

	std::string str_buf(buf);
	int i = 0;
	std::string hsh;
	char t = str_buf[i];
	while (t != ' ')
	{
		hsh.push_back(t);
		i++;
		t = str_buf[i];
	}
	hash = std::stoi(hsh);

	file_str = new char[str_buf.size() + 1];
	for (int i = 0; i < str_buf.size(); i++)
		file_str[i] = buf[i];
	file_str[str_buf.size()] = '\0';
}

