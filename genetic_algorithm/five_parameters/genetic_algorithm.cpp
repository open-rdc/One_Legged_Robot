#pragma warning(disable: 4819)

#include <iostream>
#include <fstream>
#include <bitset>
#include <boost/random.hpp>
#include <boost/date_time.hpp>
#include <boost/date_time/c_local_time_adjustor.hpp>
#include <boost/chrono.hpp>
#include <boost/thread.hpp>
#include "parameter.h"

unsigned long long GetTimeStamp()
{
	namespace pt = boost::posix_time;
	namespace gg = boost::gregorian;

	typedef boost::date_time::c_local_adjustor<pt::ptime> local_adj;

	auto epoch = local_adj::utc_to_local(pt::ptime(gg::date(1970, 1, 1)));
	auto diff = pt::microsec_clock::local_time() - epoch;

	return diff.total_microseconds();
}

std::string GetTimeISOString()
{
	boost::posix_time::ptime today = boost::posix_time::second_clock::local_time();

	return boost::posix_time::to_iso_string(today);
}

void Random(int min, int max, int result[][PARAMETER_NUM], int num)
{
	boost::random::mt19937 gen(GetTimeStamp());
	boost::random::uniform_int_distribution<> dist(min, max);

	for(int i=0; i<RANDOM_MAX; i++)
	{
		result[i][num] = dist(gen);
	}
}

int Random(int min, int max)
{
	boost::random::mt19937 gen(GetTimeStamp());
	boost::random::uniform_int_distribution<> dist(min, max);

	boost::this_thread::sleep(boost::posix_time::microseconds(1000));

	return dist(gen);
}

void Initialize(int angle[][PARAMETER_NUM])
{
	Random(0, 180, angle, 0);
	Random(0, 1000, angle, 1);
	Random(0, 180, angle, 2);
	Random(0, 1000, angle, 3);
	Random(0, 2000, angle, 4);
}

void Selection(int angle[][PARAMETER_NUM], int result[][2])
{
	int temp, angle_temp;
	int target_abs[RANDOM_MAX][2];

	for(int i=0; i<RANDOM_MAX; i++)
	{
		target_abs[i][0] = std::abs(angle[i][0] - TARGET_VALUE);
		target_abs[i][1] = i;
	}

	for(int j=0; j<RANDOM_MAX-1; j++)
	{
		for(int k=j+1; k<RANDOM_MAX; k++)
		{
			if(target_abs[j][0] > target_abs[k][0])
			{
				temp = target_abs[j][0];
				angle_temp = target_abs[j][1];
				target_abs[j][0] = target_abs[k][0];
				target_abs[j][1] = target_abs[k][1];
				target_abs[k][0] = temp;
				target_abs[k][1] = angle_temp;
			}
		}
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
	int angle[RANDOM_MAX][PARAMETER_NUM];
	int result[RANDOM_MAX][2];
	int parent_cpy = 0;
	std::bitset<32> parent[RANDOM_MAX];
	std::bitset<32> child[RANDOM_MAX];

	std::ofstream ofs(GetTimeISOString() + ".csv");

	Initialize(angle);

	Selection(angle, result);

	for(int i=0; i<PARAMETER_NUM; i++)
	{
		ofs << "parameter" << i << "\t";
		for(int j=0; j<RANDOM_MAX; j++)
		{
			ofs << angle[j][i] << "\t";
		}
		ofs << "\n";
	}

	return 0;
}