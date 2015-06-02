#include "GeneticAlgorithm.h"

bool GA::LoadFile()
{
	if(!fm.OpenInputFile("Parameter.csv"))
	{
		return false;
	}

	for(int i=0; i<RANDOM_MAX; i++)
	{
		for(int j=0; j<PARAMETER_NUM; j++)
		{
			angle[i][j] = fm.GetData();
			ofs << angle[i][j] << "\t";
		}
	}

	fm.CloseInputFile();
	return true;
}

void GA::Initialize()
{
	if(!LoadFile())
	{
		std::cout << "----- Initialize -----" << std::endl;
		ofs.open(utility.GetTimeISOString() + ".csv");
		ofs << "Initialize" << std::endl;

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
				ofs << angle[i][j] << "\t";
			}
		}
	}

	
	ofs << std::endl;
}

void GA::MakeSring()
{
	ResetStr();

	for(int i=0; i<RANDOM_MAX; i++)
	{
		for(int j=0; j<PARAMETER_NUM; j++)
		{
			if(j == 0 || j == 2)
			{
				str[i] += std::to_string(angle[i][j] - ZERO_POINT);
			}
			else
			{
				str[i] += std::to_string(angle[i][j]);
			}
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
	ofs << "move_result" << std::endl;

	for(int i=0; i<RANDOM_MAX; i++)
	{
		serial.BoostWrite("s");
		for(int j=0; j<5; j++)
		{
			serial.BoostWrite(str[i]);
			boost::this_thread::sleep(boost::posix_time::milliseconds(10));
		}
		std::cout << "str[" << i << "]: " << str[i];
		boost::this_thread::sleep(boost::posix_time::seconds(SLEEP_TIME));
		for(int k=0; k<100; k++)
		{
			serial.BoostRead();
			boost::this_thread::sleep(boost::posix_time::milliseconds(50));
		}
		enc = serial.GetSerialBuf();
		std::cout << "ReadEnc: " << enc << std::endl << std::endl;
		move_result[i] = enc;
		ofs << move_result[i] << "\t";
	}
	ofs << std::endl;
}

void GA::Selection()
{
	int temp, angle_temp;
	int target[RANDOM_MAX][2];
	int parent_cpy = 0;

	std::cout << "----- Selection -----" << std::endl;
	ofs << "Selection" << std::endl;

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
			ofs << angle[result[parent_cpy][1]][n] << "\t";
			parent_cpy += 1;
		}
	}
	ofs << std::endl;
}

void GA::Crossover()
{
	std::bitset<32> mask = utility.GetMask();
	int counter = 0;
	std::cout << "----- Crossover -----" << std::endl;
	ofs << "Crossover" << std::endl;

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
			ofs << utility.DecimalToBinary(child[i][k]) << "\t";
			ofs << utility.DecimalToBinary(child[i+1][k]) << "\t";
		}
	}
	ofs << std::endl;
}

void GA::Mutation()
{
	double random;
	int mutation_pos;
	std::cout << "----- Mutation -----" << std::endl;
	ofs << "Mutation" << std::endl;

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
			ofs << angle[l][k] << "\t";
		}
	}
	ofs << std::endl;
}

void GA::ResetStr()
{
	for(int i=0; i<RANDOM_MAX; i++)
	{
		str[i] = "";
	}
}

void GA::SaveParameter()
{
	fm.OpenOutputFile("Parameter.csv");
	for(int i=0;i<RANDOM_MAX;i++)
	{
		for(int j=0;j<PARAMETER_NUM;j++)
		{
			fm.PutData(angle[i][j]);
		}
		fm.PutEndline();
	}
	fm.CloseOutputFile();
}

int main()
{
	Serial serial;
	GA ga;
	ga.Initialize();
	serial.Init();

	for(int i=0; i<LOOP_COUNT; i++)
	{
		std::cout << "LOOP_COUNT: " << i+1 << std::endl;

		ga.MakeSring();
		ga.RobotMove();
		
		ga.Selection();
		ga.Crossover();
		ga.Mutation();
	}

	serial.close();

	return 0;
}