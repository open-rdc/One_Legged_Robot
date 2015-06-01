#include "FileManager.h"


/*FileManager::FileManager(void)
{
}


FileManager::~FileManager(void)
{
}
*/
bool FileManager::OpenInputFile(char* str)
{
	ifs = ifstream(str);
	if(!ifs)
	{
		cout << "ファイルが存在しないため、終了しました。" << endl;
		return false;
	}
	return true;
}

int FileManager::GetData(void)
{
	std::string _ret = "null";
	if(!ifs.eof()){
		ifs >> _ret;
		if(_ret == "null"){return 0;}
		int ret = std::stoi(_ret);
		return ret;
	}
}

void FileManager::CloseInputFile(void)
{
	ifs.close();
}

void FileManager::OpenOutputFile(char* str)
{
	ofs = ofstream(str);
}

void FileManager::PutData(int val)
{
	ofs << val;
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
	while(ifs.eof())
	{
		std::string str;
		ifs >> str;
		cout << str;
	}
}