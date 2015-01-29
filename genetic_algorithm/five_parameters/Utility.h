#ifndef UTILITY_H_
#define UTILITY_H_

#include <bitset>
#include <boost/random.hpp>
#include <boost/date_time.hpp>
#include <boost/date_time/c_local_time_adjustor.hpp>
#include <boost/chrono.hpp>
#include <boost/thread.hpp>
#include "Parameter.h"

class Utility
{
public:
	unsigned long long GetTimeStamp();
	std::string GetTimeISOString();
	void Random(int min, int max, int num);
	int Random(int min, int max);
	int GetRandom(int random_num, int parameter_num);
	unsigned long DecimalToBinary(std::bitset<32> decimal);
	std::bitset<32> BinaryToDecimal(std::bitset<32> binary);
	std::bitset<32> GetMask();
	std::bitset<32> GetMaskRandom();

private:
	int result[RANDOM_MAX][PARAMETER_NUM];
	std::bitset<32> mask;
	std::bitset<32> mask_random;

	void SetMask();
	void SetMaskRandom();
};
#endif