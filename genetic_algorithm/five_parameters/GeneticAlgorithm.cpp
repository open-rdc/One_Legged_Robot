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

void GA::Selection(int move_result[])
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
}

int GA::GetAngle(int random_num, int parameter_num)
{
	return angle[random_num][parameter_num];
}

int main()
{
	std::cout << "main" << std::endl;
	return 0;
}