#include "kmeansfiveparamater.h"


Kmeans::Kmeans(void)
{
	DataInit();
	RandomClusterInit();
}

int Kmeans::GetRandom(int min,int max)
{
	return min + (int)(rand()*(max-min+1.0)/(1.0+RAND_MAX));
}

void Kmeans::DataInit()
{
	for(int i=0;i<NUM;i++)
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
		for(int j=0;j<pNUM;j++)
		{
			individual[i][j] = pos[i][j];
		}
    }
	cout<<endl;
	loop = true;
}

void Kmeans::RandomClusterInit(void)
{
	for(int i=0; i<cNUM; i++)
    {
		center[i] = i;
    }
}


void Kmeans::CenterInit(void)
{
	for(int i=0;i<cNUM; i++)
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
	for(int i=0;i<NUM; i++){
		for(int j=0;j<cNUM; j++){
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
	for(int i=0;i<NUM; i++){
        min = distance[0][i];
        min_j = 0;
 
		for(int j=1;j<cNUM; j++){
            if(min > distance[j][i]){
                min		= distance[j][i];
                min_j	= j;
            }
        }
		if(count_Group[min_j]<hNUM){
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
		for(int i=0;i<cNUM; i++){
           
 
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
			if(same_count == cNUM){
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

void Kmeans::Clustering(void)
{
	while(loop)
	{
		CenterInit();
		Distance();
		GetCenter();
		ChangeCluster();
	}
}

void Kmeans::GetCenterPos(int c[cNUM][pNUM])
{
	for(int i=0;i<cNUM;i++)
	{
		for(int j=0;j<pNUM;j++)
		{
			c[i][j] = (int)pos[center[i]][j];
		}
	}
}

void Kmeans::GetCluster(int c[hNUM][pNUM],int clusterNum)
{
	for(int i=0;i<hNUM;i++)
	{
		for(int j=0;j<pNUM;j++)
		{
			c[i][j] = (int)pos[cluster[clusterNum][i]][j];
		}
	}
}