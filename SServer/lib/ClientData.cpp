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
	size = _msize(a) / sizeof(char) - 1;
	data = new char[size + 1];
	for (int i = 0; i < size; i++)
		data[i] = a[i + 1];
	data[size] = '\0';
	file_str = nullptr;
	SetString();
}

void Zip::SetString()
{
	int r = rand();

	std::string name_file;
	char t = data[0];
	int i = 0;
	while (t != ' ')
	{
		name_file.push_back(t);
		i++;
		t = data[i];
	}

	std::string path_zip = "C:/Users/1/Desktop/Server/" + std::to_string(r + 1) + ".zip";
	std::fstream f(path_zip, std::ios::binary | std::ios::out);

	f.write(data, size);

	f.close();

	system(("\"7za.exe\" e -y " + path_zip + " -oC:/Users/1/Desktop/Server/").c_str());

	std::ifstream is("C:/Users/1/Desktop/Server/" + name_file);
	std::string rr;
	if (is.is_open())
	{
		getline(is, rr);
	}

	int size_res = rr.size() + 1;
	file_str = new char[size_res];
	for (int i = 0; i < rr.size(); i++)
		file_str[i] = rr[i];
	file_str[size_res - 1] = '\0';

	t = file_str[size_res - 2];
	i = size_res - 2;
	std::string hsh;
	while (t != ' ')
	{
		hsh.push_back(t);
		i--;
		t = file_str[i];
	}
	std::reverse(hsh.begin(), hsh.end());
	hash = std::stoi(hsh);

}


Zip2::Zip2(char* a)
{
	size = _msize(a) / sizeof(char) - 1;
	data = new char[size + 1];
	for (int i = 0; i < size; i++)
		data[i] = a[i + 1];
	data[size] = '\0';
	file_str = nullptr;
	SetString();
}

void Zip2::SetString()
{
	int r = rand();

	std::string name_file;
	char t = data[0];
	int i = 0;
	while (t != ' ')
	{
		name_file.push_back(t);
		i++;
		t = data[i];
	}

	std::string path_zip = "C:/Users/1/Desktop/Server/" + std::to_string(r + 1) + ".zip";
	std::fstream f(path_zip, std::ios::binary | std::ios::out);

	f.write(data, size);

	f.close();

	system(("\"7za.exe\" e -y " + path_zip + " -oC:/Users/1/Desktop/Server/").c_str());

	std::ifstream is("C:/Users/1/Desktop/Server/" + name_file);
	std::string rr;
	if (is.is_open())
	{
		getline(is, rr);
	}

	int size_res = rr.size() + 1;
	file_str = new char[size_res];
	for (int i = 0; i < rr.size(); i++)
		file_str[i] = rr[i];
	file_str[size_res - 1] = '\0';

	i = 0;
	std::string hsh;
	t = file_str[i];
	while (t != ' ')
	{
		hsh.push_back(t);
		i++;
		t = file_str[i];
	}
	hash = std::stoi(hsh);
}

