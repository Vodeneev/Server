#include<iostream>
#include<fstream>
#include<string>

class ClientData
{
public:
	virtual char* GetString() = 0;
	virtual int Size() = 0;
	virtual ~ClientData(){}
};

class Simple : public ClientData
{
	char* data;
	int size;
	char* str;
public:
	Simple();

	Simple(std::string a);
	
	int Size() override
	{
		return size;
	}

	char* GetString() override;
	
	~Simple()
	{
		delete[] data;
		delete[] str;
	}
};

class Zip : public ClientData
{
	char* data;
	int hash;
	int size;
	char* str;
public:
	Zip();
	
	Zip(std::string a, int hash, char type);
	
	int Size() override
	{
		return size;
	}

	void SetString(char type);
	
	char* GetString() override
	{
		return str;
	}

	~Zip() {
		delete[] data;
		delete[] str;
	}
};
