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

	int size_res = msg.size() + 13;
	uLong comprLen = size_res;
	Byte* res = new Byte[size_res];
	int returnCode;
	returnCode = compress(res, &comprLen, (const Byte*)msg.c_str(), msg.size() + 1);

	str = new char[comprLen + 1];
	if (type == 'b')
		str[0] = 'b';
	else
		str[0] = 'c';
	for (int i = 1; i < comprLen + 1; i++)
		str[i] = char(res[i - 1]);
	size = comprLen + 1;
}
