#include "FileManager.h"


FileManager::FileManager(void)
{
}


FileManager::~FileManager(void)
{
}

bool FileManager::OpenInputFile(char* name)
{
	ifs = ifstream(name);
	if(!ifs)
	{
		cout << "ファイルが存在しないため、終了しました。" << endl;
		return false;
	}
	else if(ifs.fail())
	{
		cout << "読み取りに失敗しました。" << endl;
		return false;
	}
	return true;
}

int FileManager::GetData(void)
{
	std::string _ret;
	if(!ifs.eof()){
		getline(ifs,_ret,',');
		int ret = stoi(_ret);
		return ret;
	}
}

void FileManager::CloseInputFile(void)
{
	ifs.close();
}

void FileManager::OpenOutputFile(char* name)
{
	ofs = ofstream(name);
}

void FileManager::PutData(int val)
{
	ofs << val << ',';
}

void FileManager::PutData(std::string  str)
{
	ofs << str;
}

void FileManager::CloseOutputFile(void)
{
	ofs.close();
}

void FileManager::PutEndline()
{
	ofs << endl;
}

void FileManager::DisplayAllData()
{
	while(!ifs.eof())
	{
		std::string str;
		getline(ifs,str,',');
		cout << str << ' ';
	}
}

int FileManager::stoi(std::string str)
{
	int ret;
	std::stringstream ss;
	ss << str;
	ss >> ret;
	return ret;
}