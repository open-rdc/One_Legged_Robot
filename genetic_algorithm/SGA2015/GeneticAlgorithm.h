#ifndef GENETICALGORITHM_H_
#define GENETICALGORITHM_H_

#include "parameter.h"
#include "Utility.h"
#include "Serial.h"
#include "FileManager.h"

class GA
{
public:
	void Initialize();
	void Selection();
	void Crossover();
	void Mutation();
	void MakeSring();
	void RobotMove();
	void SaveParameter();
	void SaveRandomParameter();
	void SaveGenerationParameter();
	int loopNo;

private:
	Utility utility;
	Serial serial;
	int angle[RANDOM_MAX][PARAMETER_NUM];
	int result[RANDOM_MAX][2];
	std::string str[RANDOM_MAX];
	int move_result[RANDOM_MAX];
	std::bitset<32> parent[RANDOM_MAX][PARAMETER_NUM];
	std::bitset<32> child[RANDOM_MAX][PARAMETER_NUM];
	std::ofstream ofs;

	void ResetStr();
	FileManager fm;
	FileManager fmg;
	bool LoadFile();
	bool LoadInitFile();
};
#endif