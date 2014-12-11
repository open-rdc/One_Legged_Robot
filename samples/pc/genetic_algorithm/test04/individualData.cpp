#include "StdAfx.h"

#define _USE_MATH_DEFINES 
#include <math.h>
#include <stdlib.h>

//#include "def.h"
#include "individualData.h"

individualData::individualData(void)
{
	gene=(double)rand()/RAND_MAX * 360 -180;
	eva = 0;
	cluster = 0;
}
void individualData::setRandom(void)
{
	gene=(double)rand()/RAND_MAX * 360 -180;
	eva = 0;
	cluster = 0;
}

void individualData::setGene(double val)
{
	if(fabs(val)<180)	gene = val;
	else				gene = fabs(val)/val * 180;
}

void individualData::setEva(double val)
{
	eva = val;
}

void individualData::setCluster(int num)
{
	if(num>=0 && num<10)	cluster = num;
	else					cluster = 0;
}

double individualData::getGene(void)
{
	return gene;
}

double individualData::getEva(void)
{
	return eva;
}

int individualData::getCluster(void)
{
	return cluster;
}

individualData::~individualData(void)
{
}
