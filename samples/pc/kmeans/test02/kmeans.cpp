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

int individual[NUM], centerpoint[cNUM];
int point_counter[cNUM]={};
int individualsum[cNUM]={};
int same_count=0;
bool loop=true;

int GetRandom(int min,int max)
{
	return min + (int)(rand()*(max-min+1.0)/(1.0+RAND_MAX));
}

void initialize(){
	for(int i=0; i<NUM; i++){
		individual[i]=GetRandom(0,100);
	}
}

void centerinitialize(){
	for(int j=0; j<cNUM; j++){
		centerpoint[j]=GetRandom(0,100);
		cout<<"centerNo["<<j<<"]="<<centerpoint[j]<< endl;
	}
}

void clustering(){
	int distance[NUM][cNUM];
	int min[NUM][cNUM];

	while (loop)
	{
		for(int i=0; i<NUM; i++){
		for(int j=0; j<cNUM; j++){
			distance[i][j]=abs(individual[i]-centerpoint[j]);
		}
	}

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

		for(int i=0;i<cNUM; i++){
			if(point_counter[i] != 0){
				if((individualsum[i] / point_counter[i]) == centerpoint[i])
						same_count ++;
				
				centerpoint[i] = individualsum[i] / point_counter[i];
			}

			if(same_count == cNUM){
				loop=false;
			}
			cout<<"new centerpoint["<<i<<"]:"<<centerpoint[i]<<endl;
		}
		cout<<endl;
	}	
}

int main()
{	
	srand((unsigned int)time(NULL));

	ofstream ofs(std::to_string((unsigned int)time(NULL)) + ".csv");
	
	initialize();

	centerinitialize();

	cout<<endl;

	clustering();
	
}
