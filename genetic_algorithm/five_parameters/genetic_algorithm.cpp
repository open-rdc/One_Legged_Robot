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

void Crossover(std::bitset<32> parent[][PARAMETER_NUM], std::bitset<32> child[][PARAMETER_NUM])
{
	std::bitset<32> mask = SetMask();
	int counter = 0;

	for(int k=0; k<PARAMETER_NUM; k++)
	{
		for(int i=0; i<RANDOM_MAX; i+=2)
		{	
			counter += 2;
			if(counter == INDIVIDUALS_NUMBER)
			{
				mask = SetMaskRandom();
				counter = 0;
			}

			for(size_t j=0; j<parent[i][k].size(); j++)
			{
				if(mask.test(j) == 0)
				{
					child[i][k].set(j, parent[i][k].test(j));
					child[i+1][k].set(j, parent[i+1][k].test(j));
				}
				else
				{
					child[i][k].set(j, parent[i+1][k].test(j));
					child[i+1][k].set(j, parent[i][k].test(j));
				}
			}
		}
	}
}

void Mutation(std::bitset<32> child[][PARAMETER_NUM])
{
	double random;
	int mutation_pos;

	for(int j=0; j<PARAMETER_NUM; j++)
	{
		for(int i=0; i<RANDOM_MAX; i++)
		{
			random = Random(0, 100) * 0.01;

			if(random <= MUTATION_RATE)
			{
				mutation_pos = Random(0, MUTATION_POS);
				child[i][j].flip(mutation_pos);
			}
		}
	}
}

int main()
{
	int angle[RANDOM_MAX][PARAMETER_NUM];
	int result[RANDOM_MAX][2];
	int parent_cpy = 0;
	std::bitset<32> parent[RANDOM_MAX][PARAMETER_NUM];
	std::bitset<32> child[RANDOM_MAX][PARAMETER_NUM];

	std::ofstream ofs(GetTimeISOString() + ".csv");

	Initialize(angle);

	Selection(angle, result);

	for(int i=0; i<LOOP_COUNT; i++)
	{
		std::cout << "LOOP_COUNT:" << i << std::endl;
		ofs << "No." << i+1 << std::endl;

		for(int i=0; i<PARAMETER_NUM; i++)
		{
			for(int j=0; j<RANDOM_MAX; j++)
			{
				ofs << angle[j][i] << "\t";
			}
			ofs << std::endl;
		}

		ofs << "Selection" << std::endl;
		for(int j=0; j<PARAMETER_NUM; j++)
		{
			for(int k=0; k<RANDOM_MAX; k++)
			{
				if(parent_cpy == INDIVIDUALS_NUMBER)
				{
					parent_cpy = 0;
				}
				parent[k][j] = BinaryToDecimal(angle[result[parent_cpy][1]][j]);
				ofs << angle[result[parent_cpy][1]][j] << "\t";
				parent_cpy += 1;
			}
			ofs << std::endl;
		}

		Crossover(parent, child);

		ofs << "Crossover" << std::endl;

		for(int m=0; m<PARAMETER_NUM; m++)
		{
			for(int l=0; l<RANDOM_MAX; l++)
			{
				ofs << DecimalToBinary(child[l][m]) << "\t";
			}
			ofs << std::endl;
		}

		Mutation(child);

		ofs << "Mutation" << std::endl;

		for(int o=0; o<PARAMETER_NUM; o++)
		{
			for(int l=0; l<RANDOM_MAX; l++)
			{
				angle[l][o] = DecimalToBinary(child[l][o]);
				ofs  << angle[l][o] << "\t";
			}
			ofs << std::endl;
		}
	}

	ofs << "final_result" << std::endl;
	Selection(angle, result);
	for(int p=0; p<PARAMETER_NUM; p++)
	{
		for(int m=0; m<INDIVIDUALS_NUMBER; m++)
		{
			ofs << angle[result[m][1]][p] << "\t";
		}
		ofs << std::endl;
	}

	return 0;
}