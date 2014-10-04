#include <iostream>
#include <boost/random.hpp>
#include <boost/date_time.hpp>
#include <boost/date_time/c_local_time_adjustor.hpp>
#include "parameter.h"

__int64 GetTimeStamp()
{
	namespace pt = boost::posix_time;
	namespace gg = boost::gregorian;

	typedef boost::date_time::c_local_adjustor<pt::ptime> local_adj;

	auto epoch = local_adj::utc_to_local(pt::ptime(gg::date(1970, 1, 1)));
	auto diff = pt::microsec_clock::local_time() - epoch;

	return diff.total_microseconds();
}

void Random(int min, int max, int *result)
{
	boost::random::mt19937 gen(GetTimeStamp());
	boost::random::uniform_int_distribution<> dist(min, max);

	for(int i=0; i<RANDOM_MAX; i++)
	{
		result[i] = dist(gen);
	}
}

void Initialize(int *angle)
{
	Random(-90, 90, angle);
}

void Selection(int angle[RANDOM_MAX], int result[RANDOM_MAX][2])
{
	int temp, min;
	int target_abs[RANDOM_MAX][2];
	for(int i=0; i<RANDOM_MAX; i++)
	{
		target_abs[i][0] = std::abs(angle[i] - TARGET_VALUE);
		target_abs[i][1] = i;
	}

	for(int j=0; j<RANDOM_MAX; j++)
	{
		min = j;
		for(int k=j+1; k<RANDOM_MAX; k++)
		{
			if(target_abs[min][0] > target_abs[k][0])
			{
				min = k;
			}
		}
		target_abs[j][1] = target_abs[min][1];
		temp = target_abs[min][0];
		target_abs[min][0] = target_abs[j][0];
		target_abs[j][0] = temp;
	}
	for(int l=0; l<RANDOM_MAX * RANKING_RATE; l++)
	{
		for(int m=0; m<2; m++)
		{
			result[l][m] = target_abs[l][m];
		}
	}
}

int main()
{
	int angle[RANDOM_MAX];
	int result[RANDOM_MAX][2];
	
	Initialize(angle);
	
	Selection(angle, result);

	for(int i=0; i<RANDOM_MAX; i++)
	{
		std::cout << "angle[" << i << "]:" << angle[i] << std::endl;
	}

	for(int k=0; k<2; k++)
	{
		std::cout << "---- No." << k+1 << " -----" << std::endl;
		std::cout << "result_abs:" << result[k][0] << std::endl;
		std::cout << "result_angle:" << angle[result[k][1]] << std::endl;
	}

	return 0;
}