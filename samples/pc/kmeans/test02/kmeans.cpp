#include <iostream>
#include <time.h>
#include <windows.h>

using namespace std;

#define NUM 10
#define cNUM 3

int GetRandom(int min,int max)
{
	return min + (int)(rand()*(max-min+1.0)/(1.0+RAND_MAX));
}

int main()
{
	int num[10];
	srand((unsigned int)time(NULL));
	for(int i=0; i<NUM; i++){
		num[i]=i+1;
		cout <<"num["<<num[i]<<"]"<<"="<< GetRandom(0,100) << endl;
		}

	cout << endl;

	for(int j=0; j<cNUM; j++){
		num[j]=j+1;
			cout<<"num["<<num[j]<<"]"<<"="<< GetRandom(0,100) << endl;
		}
}
