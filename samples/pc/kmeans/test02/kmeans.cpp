#include <iostream>
#include <fstream>
#include <string>
#include <time.h>

using namespace std;

#define NUM 10
#define cNUM 3

int GetRandom(int min,int max)
{
	return min + (int)(rand()*(max-min+1.0)/(1.0+RAND_MAX));
}


int main()
{
	int num[NUM], cnum[cNUM];
	int result[NUM][cNUM];
	srand((unsigned int)time(NULL));

	ofstream ofs(std::to_string((unsigned int)time(NULL)) + ".csv");

	for(int i=0; i<NUM; i++){
		num[i]=GetRandom(0,100);
		cout<<"No["<<i<<"] = "<<num[i]<<endl;
	}

	cout << endl;

	for(int j=0; j<cNUM; j++){
		cnum[j]=GetRandom(0,100);
			cout<<"centerNo["<<j<<"]="<<cnum[j]<< endl;
		}

	cout<<endl;
	
	for(int i=0; i<NUM; i++){
		for(int j=0; j<cNUM; j++){
			result[i][j]=abs(num[i]-cnum[j]);
			cout<<"result["<<i<<"]["<<j<<"]="<<result[i][j]<<endl;
				
		}
	}
	cout<<endl;

	int min[NUM][2];
	for(int i=0; i<NUM; i++){
		min[i][0] = result[i][0];
		min[i][1] = 0;
		for(int j=0; j<cNUM; j++){
			if(result[i][j]<min[i][0]){
				min[i][0]=result[i][j];
				min[i][1]=j;
			}
		}
		cout<<"min ["<<i<<"][0]: "<<min[i][0]<<endl;
		cout<<"min[" <<i<<"][1]: "<<min[i][1]<<endl;
	}

	int point_counter[cNUM]={};
	for(int i=0;i<NUM;i++)
	{
		for(int j=0;j<cNUM;j++)
		{
			if(min[i][1]==j)
			{
				point_counter[j]++;
			}
		}
	}

	for(int i=0; i<NUM; i++)
	{
		cout<<"----- "<<i<<"番目の個体 -----"<<endl;
		cout<<"個体の数値: "<<num[i]<<endl;
		cout<<"センターポイントの位置"<<cnum[min[i][1]]<<endl;
		cout<<"センターポイントの距離: "<<min[i][0]<<endl;
		cout<<"所属するセンターポイント: "<<min[i][1]<<endl;
		ofs << num[i] << "\t" <<cnum[min[i][1]]<<"\t"<<min[i][0] <<"\t"<< min[i][1]<<endl;
	}
	for(int i=0;i<cNUM;i++)
	{
		cout<<i<<"番目のセンターポイントに所属する個数: " << point_counter[i] << endl;
	}

}
