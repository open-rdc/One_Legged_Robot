#include <iostream>
#include <bitset>
#include <boost/random.hpp>
#include <boost/date_time.hpp>
#include <boost/date_time/c_local_time_adjustor.hpp>
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

void Random(int min, int max, int result[RANDOM_MAX])
{
	boost::random::mt19937 gen(GetTimeStamp());
	boost::random::uniform_int_distribution<> dist(min, max);

	for(int i=0; i<RANDOM_MAX; i++)
	{
		result[i] = dist(gen);
	}
}

void Initialize(int angle[RANDOM_MAX])
{
	Random(0, 180, angle);
}

void Selection(int angle[RANDOM_MAX], int result[RANDOM_MAX][2])
{
	int temp, angle_temp;
	int target_abs[RANDOM_MAX][2];

	for(int i=0; i<RANDOM_MAX; i++)
	{
		target_abs[i][0] = std::abs(angle[i] - TARGET_VALUE);
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

unsigned long DecimalToBinary(std::bitset<32> decimal)
{
	std::bitset<32> value(decimal);
	
	return value.to_ulong();
}

std::bitset<32> BinaryToDecimal(std::bitset<32> binary)
{
	std::bitset<32> value(binary);

	return value;
}

std::bitset<32> SetMask()
{
	std::bitset<32> mask_bit;
	int bit_counter = 0;
	for(size_t l=0; l<mask_bit.size(); l++)
	{
		if(bit_counter == 0)
		{
			mask_bit.set(l, 1);
			bit_counter = 1;
		}
		else
		{
			bit_counter = 0;
		}
	}

	return mask_bit;
}

void Crossover(std::bitset<32> parent1, std::bitset<32> parent2, std::bitset<32> mask, std::bitset<32> child[])
{
	for(int i=0; i<RANDOM_MAX * RANKING_RATE; i+=2)
	{
		for(size_t j=0; j<parent1.size(); j++)
		{
			if(mask.test(j) == 0)
			{
				child[i].set(j, parent1.test(j));
				child[i+1].set(j, parent2.test(j));
			}
			else
			{
				child[i].set(j, parent2.test(j));
				child[i+1].set(j, parent1.test(j));
			}
		}
	}
}

int main()
{
	int angle[RANDOM_MAX];
	int result[RANDOM_MAX][2];
	std::bitset<32> parent[RANDOM_MAX];
	std::bitset<32> child[RANDOM_MAX];
	
	Initialize(angle);
	
	Selection(angle, result);

	for(int i=0; i<RANDOM_MAX; i++)
	{
		std::cout << "angle[" << i << "]:" << angle[i] << std::endl;
	}

	for(int j=0; j<INDIVIDUALS_NUMBER; j++)
	{
		parent[j] = BinaryToDecimal(angle[result[j][1]]);
		std::cout << "---- No." << j+1 << " -----" << std::endl;
		std::cout << "result_abs:" << result[j][0] << std::endl;
		std::cout << "result_angle:" << angle[result[j][1]] << std::endl;
		std::cout << "convert_result_angle:" << parent[j] << std::endl;
	}
	
	std::cout << "----- Crossover -----" << std::endl;
	for(int k=0; k<INDIVIDUALS_NUMBER; k+=2)
	{
		Crossover(parent[k], parent[k+1], SetMask(), child);
		std::cout << "child[" << k << "]:" << DecimalToBinary(child[k]) << std::endl;
		std::cout << "child[" << k+1 << "]:" << DecimalToBinary(child[k+1]) << std::endl;
	}

	return 0;
}