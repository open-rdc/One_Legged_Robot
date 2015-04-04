#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <time.h>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

#define NUM 100
#define cNUM 3

class pos{
public:
	double a1;
	double t1;
	double a2;
	double t2;
	double w;
};

int GetRandom(int min,int max)
{
	return min + (int)(rand()*(max-min+1.0)/(1.0+RAND_MAX));
}


int main(){
	pos* centerpoint = new pos[cNUM]; 
	pos* cluster = new pos[cNUM];
 
	double count_Group[cNUM]={0,};
 
    vector< pos > individual;
	vector< double > distance[cNUM];

	double min;
	int min_j;

	//data
	for(int i=0;i<NUM;i++){
        pos tmp;
		tmp.a1 = GetRandom(0,45);
		tmp.t1 = GetRandom(0,100);
		tmp.a2 = GetRandom(0,45);
		tmp.t2 = GetRandom(0,100);
		tmp.w  = GetRandom(500,1000);
		cout<<"("<<tmp.a1<<","<<tmp.t1<<","<<tmp.a2<<","<<tmp.t2<<","<<tmp.w<<") "<<endl;
		individual.push_back(tmp);
    }
	cout<<endl;
	
 
    //random cluster, init
	for(int i=0; i<cNUM; i++)
    {
		cluster[i] = individual[i];
		centerpoint[i].a1 = individual[i].a1;
		centerpoint[i].t1 = individual[i].t1;
		centerpoint[i].a2 = individual[i].a2;
		centerpoint[i].t2 = individual[i].t2;
		centerpoint[i].w  = individual[i].w;
		distance[i].resize( NUM );
    }
	
	bool loop = true;
	
	while(loop){

		 //center init
		for(int i=0;i<cNUM; i++){
			centerpoint[i].a1 = 0;
			centerpoint[i].t1 = 0;
			centerpoint[i].a2 = 0;
			centerpoint[i].t2 = 0;
			centerpoint[i].w  = 0;
            count_Group[i] = 0;
        }
       
       
 
        // distance
		for(int i=0;i<individual.size(); i++){
			for(int j=0;j<cNUM; j++){
				double tmp_distance = sqrt ( pow( cluster[j].a1 - individual[i].a1, 2) +
					pow( cluster[j].t1 - individual[i].t1, 2) + 
					pow( cluster[j].a2 - individual[i].a2, 2) +
					pow( cluster[j].t2 - individual[i].t2, 2) + 
					pow( cluster[j].w - individual[i].w, 2));
                distance[j][i] = tmp_distance;
            }
        }
 
        //get center
		for(int i=0;i<individual.size(); i++){
            min = distance[0][i];
            min_j = 0;
 
			for(int j=1;j<cNUM; j++){
                if(min > distance[j][i]){
                    min = distance[j][i];
                    min_j = j;
                }
            }
			centerpoint[ min_j ].a1 += individual[i].a1;
			centerpoint[ min_j ].t1 += individual[i].t1;
			centerpoint[ min_j ].a2 += individual[i].a2;
			centerpoint[ min_j ].t2 += individual[i].t2;
			centerpoint[ min_j ].w += individual[i].w;
            count_Group[min_j]++;
        }
 
        //change cluster
        int same_count = 0;
		for(int i=0;i<cNUM; i++){
           
 
            if(count_Group[i] != 0){
				if((centerpoint[i].a1 / count_Group[i]) == cluster[i].a1 
                && (centerpoint[i].t1 / count_Group[i]) == cluster[i].t1
				&& (centerpoint[i].a2 / count_Group[i]) == cluster[i].a2
				&& (centerpoint[i].t2 / count_Group[i]) == cluster[i].t2
				&& (centerpoint[i].w / count_Group[i]) == cluster[i].w)
                        same_count ++;
               
				cluster[i].a1 = centerpoint[i].a1 / count_Group[i];
				cluster[i].t1 = centerpoint[i].t1 / count_Group[i];
				cluster[i].a2 = centerpoint[i].a2 / count_Group[i];
				cluster[i].t2 = centerpoint[i].t2 / count_Group[i];
				cluster[i].w = centerpoint[i].w / count_Group[i];
            }
			if(same_count == cNUM){
                loop=false;
            }

			cout<<fixed<<setprecision(2);
			cout<<"("<<cluster[i].a1<<","<<cluster[i].t1<<","<<cluster[i].a2<<","<<cluster[i].t2<<","<<cluster[i].w<<") "<<endl;
				   
        }cout<<endl;

	}

}
	