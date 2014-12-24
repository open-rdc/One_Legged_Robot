#include <iostream>
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

	int min[10];
	for(int i=0; i<NUM; i++){
		min[i] = result[i][0];
		for(int j=0; j<cNUM; j++){
			if(result[i][j]<min[i]){
				min[i]=result[i][j];
			}
		}
		cout<<"min ["<<i<<"]: "<<min[i]<< endl;
	}

	cout<<endl;		

}

	
