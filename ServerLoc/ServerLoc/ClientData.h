#include <iostream>
#include <fstream>
#include <string>
#include "zlib.h"

class ClientData
{
public:
	virtual std::string GetString() = 0;
	virtual ~ClientData(){}
};


class Simple : public ClientData
{
	char* data;
	char* file_str;
	int size;
public:
	Simple();
	
	Simple(char* a);
	
	void SetString();
	
	std::string GetString() override
	{
		std::string res(file_str);
		res = "Client ID: " + res;
		return res;
	}

	~Simple() override
	{
		delete[] data;
		delete[] file_str;
	}
};

class Zip : public ClientData
{
protected:
	Byte* data;
	int hash;
	int size;
	char* file_str;
public:
	Zip();

	Zip(char* a);
	
	void SetString();

	std::string GetString() override
	{
		std::string res(file_str);
		int un_zip_size = res.size();
		int i = 0;
		while (res[i] != ' ')
		{
			i++;
		}
		res.insert(i + 1, "  Hash: ");
		res = "Client ID: " + res;
		res += "   Zip_size: " + std::to_string(size) + "   Un_Zip_size: " + std::to_string(un_zip_size);
		return res;
	}

	~Zip() override
	{
		delete[] data;
		delete[] file_str;
	}
};

class Zip2 : public Zip
{

public:
	Zip2(char* a);
	
	void SetString();
	
	std::string GetString() override
	{
		std::string str(file_str);
		std::string hash, id;
		int un_zip_size = str.size();
		int i = 0;
		while (str[i] != ' ')
		{
			hash.push_back(str[i]);
			i++;
		}
		i++;
		while (i < str.size())
		{
			id.push_back(str[i]);
			i++;
		}
		
		std::string res = "Client ID: " + id + "  Hash: " + hash;
		res += "   Zip_size: " + std::to_string(size) + "   Un_Zip_size: " + std::to_string(un_zip_size);
		return res;
	}

	~Zip2() override
	{
		delete[] data;
		delete[] file_str;
	}
};
