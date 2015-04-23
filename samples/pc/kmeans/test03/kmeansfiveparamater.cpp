#include "kmeansfiveparamater.h"




int kmeans::GetRandom(int min,int max)
{
	return min + (int)(rand()*(max-min+1.0)/(1.0+RAND_MAX));
}

void kmeans::DataInit()
{
	for(int i=0;i<NUM;i++)
	{
		pos[i][a1]	 = GetRandom(0,45);
		pos[i][t1]	 = GetRandom(0,100);
		pos[i][a2]	 = GetRandom(0,45);
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

void kmeans::RandomClusterInit(void)
{
	for(int i=0; i<cNUM; i++)
    {
		cluster[i] = i;
    }
}


void kmeans::CenterInit(void)
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

void kmeans::Distance(void)
{
	for(int i=0;i<NUM; i++){
		for(int j=0;j<cNUM; j++){
			double tmp_distance = sqrt ( 
				pow( pos[cluster[j]][a1]	- individual[i][a1], 2) +
				pow( pos[cluster[j]][t1]	- individual[i][t1], 2) + 
				pow( pos[cluster[j]][a2]	- individual[i][a2], 2) +
				pow( pos[cluster[j]][t2]	- individual[i][t2], 2) + 
				pow( pos[cluster[j]][w]		- individual[i][w], 2));
			distance[j][i] = tmp_distance;
         }
    }
}

void kmeans::GetCenter(void)
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
		centerpoint[ min_j ][a1]	+= individual[i][a1];
		centerpoint[ min_j ][t1]	+= individual[i][t1];
		centerpoint[ min_j ][a2]	+= individual[i][a2];
		centerpoint[ min_j ][t2]	+= individual[i][t2];
		centerpoint[ min_j ][w]		+= individual[i][w];
        count_Group[min_j]++;
    }
}

void kmeans::ChangeCluster(void)
{
	int same_count = 0;
		for(int i=0;i<cNUM; i++){
           
 
            if(count_Group[i] != 0){
				if((centerpoint[i][a1]	/ count_Group[i]) == pos[cluster[i]][a1] 
                && (centerpoint[i][t1]	/ count_Group[i]) == pos[cluster[i]][t1]
				&& (centerpoint[i][a2]	/ count_Group[i]) == pos[cluster[i]][a2]
				&& (centerpoint[i][t2]	/ count_Group[i]) == pos[cluster[i]][t2]
				&& (centerpoint[i][w]	/ count_Group[i]) == pos[cluster[i]][w])
                        same_count ++;
               
				pos[cluster[i]][a1] = centerpoint[i][a1]	/ count_Group[i];
				pos[cluster[i]][t1] = centerpoint[i][t1]	/ count_Group[i];
				pos[cluster[i]][a2] = centerpoint[i][a2]	/ count_Group[i];
				pos[cluster[i]][t2] = centerpoint[i][t2]	/ count_Group[i];
				pos[cluster[i]][w]	= centerpoint[i][w]		/ count_Group[i];
            }
			if(same_count == cNUM){
                loop=false;
        }

		cout	<<fixed<<setprecision(2);
		cout	<<"("<<pos[cluster[i]][a1]
				<<","<<pos[cluster[i]][t1]
				<<","<<pos[cluster[i]][a2]
				<<","<<pos[cluster[i]][t2]
				<<","<<pos[cluster[i]][w]<<") "
		<<endl;
			   
    }cout<<endl;
}

void kmeans::Clustering(void)
{
	DataInit();
	RandomClusterInit();
	while(loop)
	{
		CenterInit();
		Distance();
		GetCenter();
		ChangeCluster();
	}
}

void kmeans::GetCluster(double c[cNUM][pNUM])
{
	for(int i=0;i<cNUM;i++)
	{
		for(int j=0;j<pNUM;j++)
		{
			c[i][j] = pos[cluster[i]][j];
		}
	}
}

int main()
{
	kmeans km;
	km.Clustering();
	return 0;
}