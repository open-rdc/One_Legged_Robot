#ifndef GENETICALGORITHM_H_
#define GENETICALGORITHM_H_

#include "parameter.h"
#include "Utility.h"
#include "Serial.h"
#include "kmeansfiveparamater.h"

class GA
{
public:
	void Initialize();
	void Selection(int c);
	void Crossover();
	void Mutation();
	void MakeSring(int c);
	void RobotMove();
	void DisplayEvaluatedValue();
	void Clustering(void);
	void InitEvalValue(void);

private:
	Utility utility;
	Serial serial;
	Kmeans kmeans;
	int angle[CLUST_PARAM_NUM][PARAMETER_NUM];
	int result[CLUST_PARAM_NUM][2];
	std::string str[CLUST_PARAM_NUM];
	int move_result[CLUST_PARAM_NUM];
	std::bitset<32> parent[CLUST_PARAM_NUM][PARAMETER_NUM];
	std::bitset<32> child[CLUST_PARAM_NUM][PARAMETER_NUM];
	std::ofstream ofs;
	int EvalValue[CLUSTER_NUM];

	void ResetStr();
};
#endif