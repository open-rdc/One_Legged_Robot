#include "GeneticAlgorithm.h"

void GA::Initialize()
{
	utility.Random(0, 450, 0);
	utility.Random(0, 100, 1);
	utility.Random(0, 450, 2);
	utility.Random(0, 100, 3);
	utility.Random(500, 1000, 4);

	for(int i=0; i<RANDOM_MAX; i++)
	{
		for(int j=0; j<PARAMETER_NUM; j++)
		{
			angle[i][j] = utility.GetRandom(i, j);
		}
	}
}

void GA::MakeSring()
{
	ResetStr();

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

void GA::RobotMove()
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

void GA::Selection()
{
	int temp, angle_temp;
	int target[RANDOM_MAX][2];
	int parent_cpy = 0;

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

	for(int l=0; l<INDIVIDUALS_NUMBER; l++)
	{
		for(int m=0; m<2; m++)
		{
			result[l][m] = target[l][m];
		}
	}

	for(int n=0; n<PARAMETER_NUM; n++)
	{
		for(int o=0; o<RANDOM_MAX; o++)
		{
			if(parent_cpy == INDIVIDUALS_NUMBER)
			{
				parent_cpy = 0;
			}
			parent[o][n] = utility.BinaryToDecimal(angle[result[parent_cpy][1]][n]);
			parent_cpy += 1;
		}
	}
}

void GA::Crossover()
{
	std::bitset<32> mask = utility.GetMask();
	int counter = 0;

	for(int k=0; k<PARAMETER_NUM; k++)
	{
		for(int i=0; i<RANDOM_MAX; i+=2)
		{	
			counter += 2;
			if(counter == INDIVIDUALS_NUMBER)
			{
				mask = utility.GetMaskRandom();
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

void GA::Mutation()
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

	for(int k=0; k<PARAMETER_NUM; k++)
	{
		for(int l=0; l<RANDOM_MAX; l++)
		{
			angle[l][k] = utility.DecimalToBinary(child[l][k]);
		}
	}
}

void GA::ResetStr()
{
	for(int i=0; i<RANDOM_MAX; i++)
	{
		str[i] = "";
	}
}

int main()
{
	Serial serial;
	GA ga;
	ga.Initialize();
	serial.Init();

	for(int i=0; i<LOOP_COUNT; i++)
	{
		ga.MakeSring();
		ga.RobotMove();
		
		ga.Selection();
		ga.Crossover();
		ga.Mutation();
	}

	serial.close();

	return 0;
}