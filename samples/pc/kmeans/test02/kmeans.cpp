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
	int sum=0;
	int num[NUM], cnum[cNUM];
	unsigned int n;
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

	for(int i=0; i<NUM; i++){
		int min = result[i][0];
		for(int j=0; j<cNUM; j++){
			if(result[i][j]<min){
				min=result[i][j];
				cout<<"result["<<i<<"]["<<j<<"]="<<min<<endl;
			}
		}
	}

	cout<<endl;		

	}

	
