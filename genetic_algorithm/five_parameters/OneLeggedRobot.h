#ifndef ONELEGGEDROBOT_H_
#define ONELEGGEDROBOT_H_

#include "Serial.h"
#include "GeneticAlgorithm.h"
#include "parameter.h"

class OLR
{
public:
	void MakeSring();
	void RobotMove();
	int GetMoveResult(int random_num);

private:
	Serial serial;
	GA ga;
	int angle[RANDOM_MAX][PARAMETER_NUM];
	std::string str[RANDOM_MAX];
	int move_result[RANDOM_MAX];

	void SetAngle();
};
#endif