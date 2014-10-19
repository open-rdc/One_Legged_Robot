#include <iostream>
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

void Random(int min, int max, int result[RANDOM_MAX])
{
	boost::random::mt19937 gen(GetTimeStamp());
	boost::random::uniform_int_distribution<> dist(min, max);

	for(int i=0; i<RANDOM_MAX; i++)
	{
		result[i] = dist(gen);
	}
}

int Random(int min, int max)
{
	boost::random::mt19937 gen(GetTimeStamp());
	boost::random::uniform_int_distribution<> dist(min, max);

	boost::this_thread::sleep(boost::posix_time::microseconds(1000));

	return dist(gen);
}

void Initialize(int angle[])
{
	Random(0, 180, angle);
}

void Selection(int angle[], int result[][2])
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

	for(size_t i=0; i<mask_bit.size(); i++)
	{
		if(bit_counter == 0)
		{
			mask_bit.set(i, 1);
			bit_counter = 1;
		}
		else
		{
			bit_counter = 0;
		}
	}

	return mask_bit;
}

std::bitset<32> SetMaskRandom()
{
	std::bitset<32> mask_bit;
	int bit_counter = 0;

	for(size_t i=0; i<mask_bit.size(); i++)
	{
		bit_counter = Random(0, 1);

		if(bit_counter == 0)
		{
			mask_bit.set(i, 1);
		}
	}

	return mask_bit;
}

void Crossover(std::bitset<32> parent[], std::bitset<32> child[])
{
	std::bitset<32> mask = SetMask();
	int counter = 0;

	for(int i=0; i<RANDOM_MAX; i+=2)
	{	
		counter += 2;
		if(counter == INDIVIDUALS_NUMBER)
		{
			mask = SetMaskRandom();
			counter = 0;
		}

		for(size_t j=0; j<parent[i].size(); j++)
		{
			if(mask.test(j) == 0)
			{
				child[i].set(j, parent[i].test(j));
				child[i+1].set(j, parent[i+1].test(j));
			}
			else
			{
				child[i].set(j, parent[i+1].test(j));
				child[i+1].set(j, parent[i].test(j));
			}
		}
	}
}

void Mutation(std::bitset<32> child[])
{
	double random;
	int mutation_pos;

	for(int i=0; i<RANDOM_MAX; i++)
	{
		random = Random(0, 100) * 0.01;

		if(random <= MUTATION_RATE)
		{
			mutation_pos = Random(0, child[i].size() / 2);
			child[i].flip(mutation_pos);
		}
	}
}

int main()
{
	int angle[RANDOM_MAX];
	int result[RANDOM_MAX][2];
	int parent_cpy = 0;
	std::bitset<32> parent[RANDOM_MAX];
	std::bitset<32> child[RANDOM_MAX];
	
	Initialize(angle);
	
	for(int i=0; i<LOOP_COUNT; i++)
	{
		std::cout << "LOOP_COUNT:" << i << std::endl;

		Selection(angle, result);

		for(int j=0; j<RANDOM_MAX; j++)
		{
			if(parent_cpy == INDIVIDUALS_NUMBER)
			{
				parent_cpy = 0;
			}
			parent[j] = BinaryToDecimal(angle[result[parent_cpy][1]]);
			parent_cpy += 1;
		}

		for(int k=0; k<INDIVIDUALS_NUMBER; k++)
		{
			std::cout << "---- No." << k+1 << " -----" << std::endl;
			std::cout << "result_angle:" << angle[result[k][1]] << std::endl;
		}
	
		std::cout << "----- Crossover -----" << std::endl;
		Crossover(parent, child);

		std::cout << "----- Mutation -----" << std::endl;
		Mutation(child);

		for(int l=0; l<RANDOM_MAX; l++)
		{
			angle[l] = DecimalToBinary(child[l]);
		}
	}

	Selection(angle, result);
	for(int m=0; m<INDIVIDUALS_NUMBER; m++)
	{
		std::cout << "child[" << m << "]:" << angle[result[m][1]] << std::endl;
	}

	return 0;
}