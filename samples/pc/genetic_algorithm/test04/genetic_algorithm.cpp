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

void Random(int min, int max, int result[RANDOM_MAX])
{
	boost::random::mt19937 gen(GetTimeStamp());
	boost::random::uniform_int_distribution<> dist(min, max);

	for(int i=0; i<RANDOM_MAX; i++)
	{
		result[i] = dist(gen);
	}	
}

void CenterRandom(int min, int max, int centerpoint[cNUM])
{
	boost::random::mt19937 gen(GetTimeStamp());
	boost::random::uniform_int_distribution<> dist(min, max);

	for(int j=0; j<cNUM; j++)
	{
		centerpoint[j]=dist(gen);
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

void CenterInitialize(int centerpoint[])
{
	CenterRandom(0, 180, centerpoint);
}

void clustering(int angle[], int centerpoint[]){
	int distance[RANDOM_MAX][cNUM];
	int min[RANDOM_MAX][cNUM];
	int point_counter[cNUM]={};
	int individualsum[cNUM]={};
	int same_count = 0;
	int cluster_anlge[RANDOM_MAX][cNUM];
	bool loop=true;

	while (loop)
	{
		for(int i=0; i<RANDOM_MAX; i++){
			for(int j=0; j<cNUM; j++){
				distance[i][j]=abs(angle[i]-centerpoint[j]);
			}
		}

		for(int i=0; i<RANDOM_MAX; i++){
			min[i][0] = distance[i][0];
			min[i][1]=0;
			for(int j=0; j<cNUM; j++){
				if(distance[i][j]<min[i][0]){
					min[i][0]=distance[i][j];
					min[i][1]=j;
				}
			}
		}

		for(int i=0; i<RANDOM_MAX; i++){
			for(int j=0; j<cNUM; j++){
				if(min[i][1]==j){
					individualsum[j] += angle[i];
					point_counter[j]++;
				}
			}
		}

		int same_count = 0;
		for(int i=0;i<cNUM; i++){
			if(point_counter[i] != 0){
				if((individualsum[i] / point_counter[i]) == centerpoint[i])
						same_count ++;
				
				centerpoint[i] = individualsum[i] / point_counter[i];
			}

			if(same_count == cNUM){
				loop=false;
			}
		}
		for(int c=0; c<cNUM; ++c){
			std::cout<<"cluster["<<c<<"]:"<<centerpoint[c]<<std::endl;
			for(int i=0; i<RANDOM_MAX; i++){
				if(min[i][1]==c){
					cluster_anlge[i][c]=angle[i];
					std::cout<<cluster_anlge[i][c]<<std::endl;
				}
			}
			std::cout<<std::endl;
		}
	}
	
}

/*
void Selection(int angle[], int result[][2])
{
	int temp, angle_temp, ctemp,center_temp;
	int target_abs[RANDOM_MAX][2];

	for(int i=0; i<RANDOM_MAX; i++)
	{
		target_abs[i][0] = std::abs(angle[i] - TARGET_VALUE);
		target_abs[i][1] = i;
	}

	for(int i=0; i<cNUM; i++)
	{
	
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
	}
 

	for(int j=0; j<cNUM; j++){
		for(int l=0; l<RANDOM_MAX * RANKING_RATE; l++)
		{
			for(int m=0; m<2; m++)
			{
				result[l][m] = target_abs[l][m];
			}
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
	int pSum=0;

	for(int j=0; j<cNUM; j++){
		pSum=0;
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
}

void Mutation(std::bitset<32> child[])
{
	double random;
	int mutation_pos;
	int pSum=0;

	for(int j=0; j<cNUM; j++)
	{
		pSum=0;
		for(int i=0; i<RANDOM_MAX; i++)
		{
			random = Random(0, 100) * 0.01;
			
			if(random <= MUTATION_RATE)
			{
				mutation_pos = Random(0, MUTATION_POS);
			    child[i].flip(mutation_pos);
			}
		}
	}
}
*/
int main()
{
	int angle[RANDOM_MAX];
	int centerpoint[cNUM];
	int result[RANDOM_MAX][2];
	int parent_cpy = 0;
	std::bitset<32> parent[RANDOM_MAX];
	std::bitset<32> child[RANDOM_MAX];

	//std::ofstream ofs(GetTimeISOString() + ".csv");
	
	Initialize(angle);

	
	CenterInitialize(centerpoint);


	clustering(angle, centerpoint);
/*
	for(int i=0; i<LOOP_COUNT; i++)
	{
		std::cout << "LOOP_COUNT:" << i << std::endl;
		ofs << "No." << i+1 << std::endl;
		
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

		ofs << "result_angle" << "\t";

		for(int k=0; k<INDIVIDUALS_NUMBER; k++)
		{
			std::cout << "---- No." << k+1 << " -----" << std::endl;
			std::cout << "result_angle:" << angle[result[k][1]] << std::endl;
			ofs << angle[result[k][1]] << "\t";
		}
		ofs << std::endl;
	
		std::cout << "----- Crossover -----" << std::endl;
		Crossover(parent, child);

		ofs << "Crossover" << "\t";

		for(int l=0; l<RANDOM_MAX; l++)
		{
			ofs << DecimalToBinary(child[l]) << "\t";
		}
		ofs << std::endl;

		std::cout << "----- Mutation -----" << std::endl;
		Mutation(child);

		ofs << "Mutation" << "\t";

		for(int l=0; l<RANDOM_MAX; l++)
		{
			angle[l] = DecimalToBinary(child[l]);
			ofs  << angle[l] << "\t";
		}
		ofs << std::endl;
	}

	ofs << "final_result" << "\t";
	Selection(angle, result);
	for(int m=0; m<INDIVIDUALS_NUMBER; m++)
	{
		std::cout << "child[" << m << "]:" << angle[result[m][1]] << std::endl;
		ofs << angle[result[m][1]] << "\t";
	}
	ofs << std::endl;
*/
	return 0;
}