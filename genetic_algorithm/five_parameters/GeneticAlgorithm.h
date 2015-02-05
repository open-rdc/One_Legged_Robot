#ifndef GENETICALGORITHM_H_
#define GENETICALGORITHM_H_

#include "parameter.h"
#include "Utility.h"

class GA
{
public:
	void Initialize();
	void Selection(int move_result[]);
	void Crossover();
	void Mutation();
	int GetAngle(int random_num, int parameter_num);

private:
	Utility utility;
	int angle[RANDOM_MAX][PARAMETER_NUM];
	int result[RANDOM_MAX][2];
	std::bitset<32> parent[RANDOM_MAX][PARAMETER_NUM];
	std::bitset<32> child[RANDOM_MAX][PARAMETER_NUM];
};
#endif