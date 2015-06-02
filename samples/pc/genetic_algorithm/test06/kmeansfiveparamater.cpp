#include "kmeansfiveparamater.h"
#include "parameter.h"


Kmeans::Kmeans(void)
{
	Init();
}

void Kmeans::Init(void)
{
	srand((unsigned int)time(NULL));
	DataInit();
	RandomClusterInit();
	ofs = ofstream("Result.csv");
}

int Kmeans::GetRandom(int min,int max)
{
	return min + (int)(rand()*(max-min+1.0)/(1.0+RAND_MAX));
}

bool Kmeans::LoadFile()
{
	if(!fmp.OpenInputFile("Parameter.csv"))
	{
		return false;
	}

	for(int i=0;i<RANDOM_MAX;i++)
	{
		for(int j=0;j<PARAMETER_NUM;j++)
		{
			pos[i][j] = fmp.GetData();
			individual[i][j] = pos[i][j];
		}
	}

	fmp.CloseInputFile();
	return true;
}

void Kmeans::DataInit()
{
	if(LoadFile())
	{
		for(int i=0;i<RANDOM_MAX;i++)
		{
			pos[i][a1]	 = GetRandom(0,450);
			pos[i][t1]	 = GetRandom(0,100);
			pos[i][a2]	 = GetRandom(0,450);
			pos[i][t2]	 = GetRandom(0,100);
			pos[i][w]	 = GetRandom(500,1000);
			cout	<<"("<<pos[i][a1]
					<<","<<pos[i][t1]
					<<","<<pos[i][a2]
					<<","<<pos[i][t2]
					<<","<<pos[i][w]<<") "
			<<endl;
			for(int j=0;j<PARAMETER_NUM;j++)
			{
				individual[i][j] = pos[i][j];
			}
		}
	}
	cout<<endl;
	loop = true;
}

void Kmeans::RandomClusterInit(void)
{
	for(int i=0; i<CLUSTER_NUM; i++)
    {
		center[i] = i;
		for(int j=0;j<CLUST_PARAM_NUM;j++)
		{
			cluster[i][j] = j + (3 * i);
		}
    }
}


void Kmeans::CenterInit(void)
{
	for(int i=0;i<CLUSTER_NUM; i++)
	{
		centerpoint[i][a1]	 = 0;
		centerpoint[i][t1]	 = 0;
		centerpoint[i][a2]	 = 0;
		centerpoint[i][t2]	 = 0;
		centerpoint[i][w]	 = 0;
        count_Group[i]		 = 0;
    }
}

void Kmeans::Distance(void)
{
	for(int i=0;i<RANDOM_MAX; i++){
		for(int j=0;j<CLUSTER_NUM; j++){
			double tmp_distance = sqrt ( 
				pow( pos[center[j]][a1]	- individual[i][a1], 2) +
				pow( pos[center[j]][t1]	- individual[i][t1], 2) + 
				pow( pos[center[j]][a2]	- individual[i][a2], 2) +
				pow( pos[center[j]][t2]	- individual[i][t2], 2) + 
				pow( pos[center[j]][w]		- individual[i][w], 2));
			distance[j][i] = tmp_distance;
         }
    }
}

void Kmeans::GetCenter(void)
{
	for(int i=0;i<RANDOM_MAX; i++){
        min = distance[0][i];
        min_j = 0;
 
		for(int j=1;j<CLUSTER_NUM; j++){
            if(min > distance[j][i]){
                min		= distance[j][i];
                min_j	= j;
            }
        }
		if(count_Group[min_j]<CLUST_PARAM_NUM){
			centerpoint[ min_j ][a1]	+= individual[i][a1];
			centerpoint[ min_j ][t1]	+= individual[i][t1];
			centerpoint[ min_j ][a2]	+= individual[i][a2];
			centerpoint[ min_j ][t2]	+= individual[i][t2];
			centerpoint[ min_j ][w]		+= individual[i][w];
			cluster[min_j][(int)count_Group[min_j]] = i;
			count_Group[min_j]++;
		}
    }
}

void Kmeans::ChangeCluster(void)
{
	int same_count = 0;
		for(int i=0;i<CLUSTER_NUM; i++){
           
 
            if(count_Group[i] != 0){
				if((centerpoint[i][a1]	/ count_Group[i]) == pos[center[i]][a1] 
                && (centerpoint[i][t1]	/ count_Group[i]) == pos[center[i]][t1]
				&& (centerpoint[i][a2]	/ count_Group[i]) == pos[center[i]][a2]
				&& (centerpoint[i][t2]	/ count_Group[i]) == pos[center[i]][t2]
				&& (centerpoint[i][w]	/ count_Group[i]) == pos[center[i]][w])
                        same_count ++;
               
				pos[center[i]][a1] = centerpoint[i][a1]	/ count_Group[i];
				pos[center[i]][t1] = centerpoint[i][t1]	/ count_Group[i];
				pos[center[i]][a2] = centerpoint[i][a2]	/ count_Group[i];
				pos[center[i]][t2] = centerpoint[i][t2]	/ count_Group[i];
				pos[center[i]][w]	= centerpoint[i][w]		/ count_Group[i];
            }
			if(same_count == CLUSTER_NUM){
                loop=false;
        }

		cout	<<fixed<<setprecision(2);
		cout	<<"("<<pos[center[i]][a1]
				<<","<<pos[center[i]][t1]
				<<","<<pos[center[i]][a2]
				<<","<<pos[center[i]][t2]
				<<","<<pos[center[i]][w]<<") "
		<<endl;
			   
    }cout<<endl;
}

void Kmeans::SaveParameter()
{
	fmp.OpenOutputFile("Parameter.csv");
	for(int i=0;i<RANDOM_MAX;i++)
	{
		for(int j=0;j<PARAMETER_NUM;j++)
		{
			fmp.PutData(pos[i][j]);
			fmp.PutData(',');
		}
		fmp.PutEndline();
	}
	fmp.CloseOutputFile();
}

void Kmeans::Clustering(void)
{
	while(loop)
	{
		CenterInit();
		
		Distance();

		GetCenter();

		ChangeCluster();
	}
	DisplayClusters();
	SaveParameter();
}

void Kmeans::GetCenterPos(int c[CLUSTER_NUM][PARAMETER_NUM])
{
	for(int i=0;i<CLUSTER_NUM;i++)
	{
		for(int j=0;j<PARAMETER_NUM;j++)
		{
			c[i][j] = (int)pos[center[i]][j];
		}
	}
}

void Kmeans::GetCluster(int c[CLUST_PARAM_NUM][PARAMETER_NUM],int clusterNum)
{
	for(int i=0;i<CLUST_PARAM_NUM;i++)
	{
		for(int j=0;j<PARAMETER_NUM;j++)
		{
			c[i][j] = (int)pos[cluster[clusterNum][i]][j];
		}
	}
}

void Kmeans::DisplayClusters()
{
	for(int i=0;i<CLUSTER_NUM;i++)
	{
		cout << "Disp Cluster Num:" << i+1 << endl;
		cout << "Center Point (" ;

		ofs << "Disp Cluster Num:" << i+1 << endl;
		ofs << "Center Point ";

		for(int j=0;j<PARAMETER_NUM;j++)
		{
			ofs << ",";
			cout << " " << (int)pos[center[i]][j] << " ";
			ofs << (int)pos[center[i]][j];
		}
		ofs << endl << endl;
		cout << ")" << endl << endl;
		for(int j=0;j<CLUST_PARAM_NUM;j++)
		{
			cout << "No." << j+1 << "("  ;
			ofs << "No." << j+1 << " ";
			for(int k=0;k<PARAMETER_NUM;k++)
			{
				cout << " " << (int)pos[cluster[i][j]][k] << " ";
				ofs << "," << (int)pos[cluster[i][j]][k];

				
			}
			ofs << endl;
			cout << ")" << endl;
		}
		cout << endl;
		ofs << endl;
	}
	cout << endl;
	ofs << endl;
}

void Kmeans::DisplayParameter()
{
	for(int i=0;i<RANDOM_MAX;i++)
	{
		cout << "No." << i+1 << "(";
		for(int j=0;j<PARAMETER_NUM;j++)
		{
			cout << " " << pos[i][j] << " ";
		}
		cout << ")" << endl;
	}
	cout << endl;
}

void Kmeans::ChangePos(int c[CLUST_PARAM_NUM][PARAMETER_NUM],int clusterNum)
{
	for(int i=0;i<CLUST_PARAM_NUM;i++)
	{
		for(int j=0;j<PARAMETER_NUM;j++)
		{
			pos[cluster[clusterNum][i]][j] = (double)c[i][j];
		}
	}
}