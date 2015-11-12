#include "GeneticAlgorithm.h"

void GA::Initialize()
{
	fm.OpenOutputFile("EvaluateResult.csv");
	kmeans.Init();
}

void GA::MakeSring()
{
	
	for(int j=0;j<kmeans.ClusterParameter[LoadingClusterNum];j++){
	cout << "angle(";
		for(int i=0;i<PARAMETER_NUM;i++)
		{
			cout << " " << angle[j][i] << " ";
		}
	cout << ")" << endl;

	}
	for(int i=0; i<kmeans.ClusterParameter[LoadingClusterNum]; i++)
	{
		for(int j=0; j<PARAMETER_NUM; j++)
		{
			if(j != 2)
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
	cout << "Robot Move" << endl;
	int enc;
	for(int i=0; i<kmeans.ClusterParameter[LoadingClusterNum]; i++)
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
		fm.PutData(enc);
		cout << "output finish" << endl; 
	}
}

void GA::Selection()
{
	int temp, angle_temp;
	int target[RANDOM_MAX][2];
	int parent_cpy = 0;
	EvalValue[LoadingClusterNum] = 0;

	std::cout << "----- Selection -----" << std::endl;

	for(int i=0; i<kmeans.ClusterParameter[LoadingClusterNum]; i++)
	{
		target[i][0] = move_result[i];
		target[i][1] = i;
	}

	for(int j=0; j<kmeans.ClusterParameter[LoadingClusterNum]-1; j++)
	{
		for(int k=j+1; k<kmeans.ClusterParameter[LoadingClusterNum]; k++)
		{
			if(target[j][0] < target[k][0])
			{
				EvalValue[LoadingClusterNum] = target[k][0];
				temp = target[j][0];
				angle_temp = target[j][1];
				target[j][0] = target[k][0];
				target[j][1] = target[k][1];
				target[k][0] = temp;
				target[k][1] = angle_temp;
//				kmeans.ChangeCenterPoint(target[j][1],LoadingClusterNum);	//中心点を評価値が高いものに変更
			}
		}
	}

	INDIVIDUALS_NUMBER = kmeans.ClusterParameter[LoadingClusterNum] * RANKING_RATE;

	for(int l=0; l<INDIVIDUALS_NUMBER; l++)
	{
		for(int m=0; m<2; m++)
		{
			result[l][m] = target[l][m];
		}
	}

	for(int n=0; n<PARAMETER_NUM; n++)
	{
		for(int o=0; o<kmeans.ClusterParameter[LoadingClusterNum]; o++)
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
	std::cout << "----- Crossover -----" << std::endl;

	for(int k=0; k<PARAMETER_NUM; k++)
	{
		for(int i=0; i<kmeans.ClusterParameter[LoadingClusterNum]; i+=2)
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
			cout << "Debug Log" << endl;
		}
	}
}

void GA::Mutation()
{
	double random;
	int mutation_pos;
	std::cout << "----- Mutation -----" << std::endl;

	for(int j=0; j<PARAMETER_NUM; j++)
	{
		for(int i=0; i<kmeans.ClusterParameter[LoadingClusterNum]; i++)
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
		for(int l=0; l<kmeans.ClusterParameter[LoadingClusterNum]; l++)
		{
			angle[l][k] = utility.DecimalToBinary(child[l][k]);
		}
	}
	fm.PutEndline();
}

void GA::DisplayEvaluatedValue()
{
	int bestValue = EvalValue[0];
	int bestCluster	= 1;
	for(int i=1;i<CLUSTER_NUM;i++)
	{
		if(bestValue < EvalValue[i])
		{
			bestValue = EvalValue[i];
			bestCluster = i+1;
		}
	}
	cout << "Best Value = " << bestValue << endl;
	cout << "Best Cluster = " << bestCluster << endl;
}

void GA::ResetStr()
{
	for(int i=0; i<kmeans.ClusterParameter[LoadingClusterNum]; i++)
	{
		str[i] = "";
	}
}

void GA::Clustering()
{
	kmeans.Clustering();
}

void GA::InitEvalValue()
{
	for(int i=0;i<CLUSTER_NUM;i++)
	{
		EvalValue[i] = 0;
	}
}


void GA::GAProcessing()
{
	serial.Init();
	Initialize();
	for(int i=0;i<LOOP_COUNT;i++)
	{
		Clustering();
		std::cout << "LOOP_COUNT: " << i+1 << std::endl; 
		fm.PutData("Loop Count:");
		fm.PutData(i+1);
		InitEvalValue();
		for(LoadingClusterNum=0;LoadingClusterNum<CLUSTER_NUM;LoadingClusterNum++){
			cout << "Cluster Count:" << LoadingClusterNum+1 << endl;
			ResetStr();
			kmeans.GetCluster(angle,LoadingClusterNum);
			fm.PutData(" Cluster No:");
			fm.PutData(LoadingClusterNum+1);
			fm.PutData("Values");
			MakeSring();
			RobotMove();
			Selection();
			Crossover();
			Mutation();
			kmeans.ChangePos(angle,LoadingClusterNum);
			cout << "Finish Cluster" << endl << endl;
		}
		DisplayEvaluatedValue();
		fm.PutEndline();
	}
	cout << "final debug 1" << endl;
	serial.close();
	fm.CloseOutputFile();
	cout << "final debug 2" << endl;
}

int main()
{
	GA ga;
	ga.GAProcessing();
	return 0;
}