#pragma once
#include <iostream>
#include <stdio.h>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;
class FileManager
{
public:
	FileManager(void);
	~FileManager(void);

	bool OpenInputFile(char* name);
	int GetData(void);
	void DisplayAllData(void);
	void CloseInputFile(void);

	void OpenOutputFile(char* name);
	void PutData(int val);
	void PutData(std::string  str);
	void PutEndline(void);
	void CloseOutputFile(void);

private:
	ifstream ifs;
	ofstream ofs;
	int stoi(std::string str);
};