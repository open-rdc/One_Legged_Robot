#pragma warning(disable: 4819)

#include <fstream>
#include <bitset>
#include "Serial.h"
#include "Utility.h"

Serial serial;
Utility utility;

void Initialize(int angle[][PARAMETER_NUM])
{
	utility.Random(0, 450, angle, 0);
	utility.Random(0, 100, angle, 1);
	utility.Random(0, 450, angle, 2);
	utility.Random(0, 100, angle, 3);
	utility.Random(500, 1000, angle, 4);
}

void MakeSring(int angle[][PARAMETER_NUM], std::string str[])
{

	for(int i=0; i<RANDOM_MAX; i++)
	{
		for(int j=0; j<PARAMETER_NUM; j++)
		{
			str[i] += std::to_string(angle[i][j]);
			str[i] += ",";
			
			if(j == PARAMETER_NUM-1)
			{
				str[i] += "\n";
			}
		}
	}
}

void RobotMove(std::string str[], int move_result[])
{
	int enc;
	for(int i=0; i<RANDOM_MAX; i++)
	{
		serial.BoostWrite("s");
		for(int j=0; j<5; j++)
		{
			serial.BoostWrite(str[i]);
			boost::this_thread::sleep(boost::posix_time::milliseconds(10));
		}
		std::cout << "str[" << i << "]: " << str[i] << std::endl;
		boost::this_thread::sleep(boost::posix_time::seconds(SLEEP_TIME));
		for(int k=0; k<100; k++)
		{
			serial.BoostRead();
			boost::this_thread::sleep(boost::posix_time::milliseconds(50));
		}
		enc = serial.GetSerialBuf();
		std::cout << "ReadEnc: " << enc << std::endl;
		move_result[i] = enc;
	}
}

void Selection(int angle[][PARAMETER_NUM], int move_result[], int result[][2])
{
	int temp, angle_temp;
	int target[RANDOM_MAX][2];

	for(int i=0; i<RANDOM_MAX; i++)
	{
		target[i][0] = move_result[i];
		target[i][1] = i;
	}

	for(int j=0; j<RANDOM_MAX-1; j++)
	{
		for(int k=j+1; k<RANDOM_MAX; k++)
		{
			if(target[j][0] < target[k][0])
			{
				temp = target[j][0];
				angle_temp = target[j][1];
				target[j][0] = target[k][0];
				target[j][1] = target[k][1];
				target[k][0] = temp;
				target[k][1] = angle_temp;
			}
		}
	}

	for(int l=0; l<RANDOM_MAX * RANKING_RATE; l++)
	{
		for(int m=0; m<2; m++)
		{
			result[l][m] = target[l][m];
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
		bit_counter = utility.Random(0, 1);

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
			random = utility.Random(0, 100) * 0.01;

			if(random <= MUTATION_RATE)
			{
				mutation_pos = utility.Random(0, MUTATION_POS);
				child[i][j].flip(mutation_pos);
			}
		}
	}
}

int main()
{
	int angle[RANDOM_MAX][PARAMETER_NUM];
	int result[RANDOM_MAX][2];
	int move_result[RANDOM_MAX];
	int parent_cpy = 0;
	std::bitset<32> parent[RANDOM_MAX][PARAMETER_NUM];
	std::bitset<32> child[RANDOM_MAX][PARAMETER_NUM];
	std::string iso_string = utility.GetTimeISOString();

	std::ofstream ofs(iso_string + ".csv");

	Initialize(angle);
	serial.Init();

	for(int i=0; i<LOOP_COUNT; i++)
	{
		std::string str[RANDOM_MAX];
		std::cout << "LOOP_COUNT:" << i << std::endl;
		ofs << "No." << i+1 << std::endl;

		MakeSring(angle, str);

		RobotMove(str, move_result);

		ofs << "move_result" << std::endl;
		for(int j=0; j<RANDOM_MAX; j++)
		{
			ofs << move_result[j] << "\t";
		}
		ofs << std::endl;

		Selection(angle, move_result, result);

		for(int j=0; j<PARAMETER_NUM; j++)
		{
			for(int k=0; k<RANDOM_MAX; k++)
			{
				if(parent_cpy == INDIVIDUALS_NUMBER)
				{
					parent_cpy = 0;
				}
				parent[k][j] = BinaryToDecimal(angle[result[parent_cpy][1]][j]);
				parent_cpy += 1;
			}
		}

		ofs << "result_angle" << std::endl;

		for(int j=0; j<PARAMETER_NUM; j++)
		{
			for(int k=0; k<INDIVIDUALS_NUMBER; k++)
			{
				ofs << angle[result[k][1]][j] << "\t";
			}
			ofs << std::endl;
		}

		std::cout << "----- Crossover -----" << std::endl;
		ofs << "Crossover" << std::endl;

		Crossover(parent, child);

		for(int m=0; m<PARAMETER_NUM; m++)
		{
			for(int l=0; l<RANDOM_MAX; l++)
			{
				ofs << DecimalToBinary(child[l][m]) << "\t";
			}
			ofs << std::endl;
		}

		std::cout << "----- Mutation -----" << std::endl;
		ofs << "Mutation" << std::endl;

		Mutation(child);

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
	Selection(angle, move_result, result);
	for(int p=0; p<PARAMETER_NUM; p++)
	{
		for(int m=0; m<INDIVIDUALS_NUMBER; m++)
		{
			ofs << angle[result[m][1]][p] << "\t";
		}
		ofs << std::endl;
	}

	serial.close();

	return 0;
}