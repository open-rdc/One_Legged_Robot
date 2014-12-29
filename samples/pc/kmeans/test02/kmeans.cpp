#include <iostream>
#include <time.h>
#include <bitset>

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

	bool loop=true;
	while (loop)
	{

	for(int i=0; i<NUM; i++){
		for(int j=0; j<cNUM; j++){
			result[i][j]=abs(num[i]-cnum[j]);
			cout<<"result["<<i<<"]["<<j<<"]="<<result[i][j]<<endl;
				
		}
	}

	cout<<endl;

	int min[NUM][cNUM];
	for(int i=0; i<NUM; i++){
		min[i][0] = result[i][0];
		min[i][1]=0;
		for(int j=0; j<cNUM; j++){
			if(result[i][j]<min[i][0]){
				min[i][0]=result[i][j];
				min[i][1]=j;
			}
			
		}
	}

	cout<<endl;

	for(int i=0; i<NUM; i++)
	{
		cout<<"----- "<<i<<"番目の個体 -----"<<endl;
		cout<<"所属するセンターポイント: "<<min[i][1]<<endl;
		cout<<"個体の数値: "<<num[i]<<endl;
		cout<<"センターポイント："<<cnum[min[i][1]]<<endl;
		cout<<"センターポイントとの距離: "<<min[i][0]<<endl;
		cout<<endl;
			
	}
	
	cout<<endl;	

	int a[cNUM]={};
	int sum[cNUM]={};
	int c[NUM]={};
	int same_count=0;
	for(int i=0; i<NUM; i++){
		for(int j=0; j<cNUM; j++){
			if(min[i][1]==j){
				a[j]++;
				sum[j] += num[i];
				c[j]=sum[j]/cnum[j];
			}
			if(same_count==j){
				loop=false;
			}
		}
		
	}
	
	
	for(int j=0; j<cNUM; j++){
		cout<<j<<"番目のセンターポイントに所属する個体数："<<a[j]<<endl;
		cout<<"個体の合計"<<sum[j]<<endl;		
	}
	
	cout<<endl;

	for(int j=0; j<cNUM; j++){
		cout<<"新しい中心点: "<<c[j]<<endl;
	}
	}
	
}

	
