#ifndef GENETICALGORITHM_H_
#define GENETICALGORITHM_H_

#include "parameter.h"
#include "Utility.h"
#include "Serial.h"
#include "kmeansthreeparamater.h"
#include "FileManager.h"

class GA
{
public:
	int LoadingClusterNum;

	void Initialize();
	void Selection();
	void Crossover();
	void Mutation();
	void MakeSring();
	void RobotMove();
	void DisplayEvaluatedValue();
	void Clustering(void);
	void InitEvalValue(void);
	void GAProcessing(void);

private:
	Utility utility;
	Serial serial;
	Kmeans kmeans;
	int angle[RANDOM_MAX][PARAMETER_NUM];
	int result[RANDOM_MAX][2];
	std::string str[RANDOM_MAX];
	int move_result[RANDOM_MAX];
	std::bitset<32> parent[RANDOM_MAX][PARAMETER_NUM];
	std::bitset<32> child[RANDOM_MAX][PARAMETER_NUM];
	int EvalValue[CLUSTER_NUM];
	FileManager fm;


	void ResetStr();
};
#endif