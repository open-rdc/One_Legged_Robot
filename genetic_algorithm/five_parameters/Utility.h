#ifndef UTILITY_H_
#define UTILITY_H_

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
	void Random(int min, int max, int result[][PARAMETER_NUM], int num);
	int Random(int min, int max);
};
#endif