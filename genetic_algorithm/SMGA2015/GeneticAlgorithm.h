#ifndef GENETICALGORITHM_H_
#define GENETICALGORITHM_H_

#define CHECK_ALGORITHM

#include <vector>
#include "parameter.h"
#include "Utility.h"
#include "Serial.h"
#include "FileManager.h"
#include "kmeans.h"

class GA
{
public:
	GA();
	~GA();	
	void Initialize();
	void Clustering();
	void SetCluster(int cluster_no);
	void Selection(int cluster_no);
	void Crossover(int cluster_no);
	void Mutation(int cluster_no);
	void MakeSring();
	void RobotMove();
	void SaveParameter();
	void SaveRandomParameter();
	void SaveGenerationParameter();
	void DevideCluster();
	void IntegrateCluster();
	int loopNo;

private:
#ifndef CHECK_ALGORITHM
	Serial serial;
#endif
	Utility utility;
	Kmeans kmeans;
	int angle[RANDOM_MAX][PARAMETER_NUM];
	int angle_org[RANDOM_MAX][PARAMETER_NUM];
	int angle_work[CLUSTER_NUM][RANDOM_MAX][PARAMETER_NUM];
	int result[RANDOM_MAX][2];
	int result_org[RANDOM_MAX][2];
	int result_work[CLUSTER_NUM][RANDOM_MAX][2];
	int individual_num[CLUSTER_NUM];
	std::string str[RANDOM_MAX];
	int move_result[RANDOM_MAX];
	std::bitset<32> parent[RANDOM_MAX][PARAMETER_NUM];
	std::bitset<32> child[RANDOM_MAX][PARAMETER_NUM];
	std::ofstream ofs;
	void ResetStr();

	FileManager fm;
	FileManager fmg;
	bool LoadInitFile();
	bool LoadFile();

	vector<double> data;
};
#endif