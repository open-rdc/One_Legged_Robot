#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <time.h>

using namespace std;

#define NUM 100
#define cNUM 3

int GetRandom(int min,int max)
{
	return min + (int)(rand()*(max-min+1.0)/(1.0+RAND_MAX));
}

int main()
{
	int individual[NUM], centerpoint[cNUM];
	int distance[NUM][cNUM];
	int min[NUM][cNUM];
	int point_counter[cNUM]={};
	int individualsum[cNUM]={};
	srand((unsigned int)time(NULL));

	ofstream ofs(std::to_string((unsigned int)time(NULL)) + ".csv");
	
	for(int i=0; i<NUM; i++){
		individual[i]=GetRandom(0,100);
		//cout<<"No["<<i<<"] = "<<individual[i]<<endl;
	}
	cout << endl;

	for(int j=0; j<cNUM; j++){
		centerpoint[j]=GetRandom(0,100);
		cout<<"centerNo["<<j<<"]="<<centerpoint[j]<< endl;
		}

	cout<<endl;

	bool loop=true;

	while (loop)
	{
		for(int i=0; i<NUM; i++){
			for(int j=0; j<cNUM; j++){
				distance[i][j]=abs(individual[i]-centerpoint[j]);
				//cout<<"result["<<i<<"]["<<j<<"]="<<distance[i][j]<<endl;	
			}
		}

		cout<<endl;

		for(int i=0; i<NUM; i++){
			min[i][0] = distance[i][0];
			min[i][1]=0;
			for(int j=0; j<cNUM; j++){
				if(distance[i][j]<min[i][0]){
					min[i][0]=distance[i][j];
					min[i][1]=j;
				}
			}
		}

		for(int i=0; i<NUM; i++){
			for(int j=0; j<cNUM; j++){
				if(min[i][1]==j){
					individualsum[j] += individual[i];
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
			cout<<"new cneterpoint:"<<centerpoint[i]<<endl;
		}
		
		cout<<endl;
	}

/*
	for(int i=0; i<NUM; i++)
	{
		cout<<"----- "<<i<<"番目の個体 -----"<<endl;
		cout<<"個体の数値: "<<individual[i]<<endl;
		cout<<"センターポイントの位置"<<centerpoint[min[i][1]]<<endl;
		cout<<"センターポイントの距離: "<<min[i][0]<<endl;
		cout<<"所属するセンターポイント: "<<min[i][1]<<endl;
		ofs<<individual[i]<<"\t"<<centerpoint[min[i][1]]<<"\t"<<min[i][0] <<"\t"<<min[i][1]<<endl;
	}
	for(int i=0;i<cNUM;i++)
	{
		cout<<i<<"番目のセンターポイントに所属する個数: "<<point_counter[i]<<endl;
		cout<<"個体の値の合計"<<sum[i]<<endl;
	}
*/
	
}
	

	
