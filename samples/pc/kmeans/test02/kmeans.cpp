#include<iostream>
#include<iomanip>
#include<algorithm>
#include<vector>
#include<string>

using namespace std;

#define kcount 3
#define data 10

class pos{
public:
	double enc;
};

int main()
{
	pos* k=new pos[kcount];
	pos* center=new pos[kcount];

	double count_group[kcount]={};

	vector<pos>datas;
	vector<double> distance[kcount];

	for(int i=0;i<data;i++){
        pos tmp;
		tmp.enc = (double)(rand()%100);
		cout<<"("<<tmp.enc<<")"<<endl;
        datas.push_back(tmp);
    }
	
	for(int i=0; i<kcount; i++)
    {
        k[i] = datas[i];
        center[i].enc = datas[i].enc;
		distance[i].resize(data);
    }
    bool loop = true;
    while(loop){ //when the k-positions are all same with next position.
       
        //center init
		for(int i=0;i<kcount; i++){
			center[i].enc= (double)(rand()%100);
            count_group[i] =(double)(rand()%100);
        }

		// distance
        for(int i=0;i<datas.size(); i++){
			for(int j=0;j<kcount; j++){
                double tmp_distance = sqrt ( pow( k[j].enc - datas[i].enc, 2));
					distance[j][i] = tmp_distance;
            }
        }
 
        //get center
        for(int i=0;i<datas.size(); i++){
            double min = distance[0][i];
            int min_j = 0;
 
			for(int j=1;j<kcount; j++){
                if(min > distance[j][i]){
                    min = distance[j][i];
                    min_j = j;
                }
            }
			center[ min_j ].enc += datas[i].enc;
            count_group[min_j]++;
        }
 
        //change K
        int same_count = 0;
		for(int i=0;i<kcount; i++){
           
 
            if(count_group[i] != 0){
                if((center[i].enc / count_group[i]) == k[i].enc)
                        same_count ++;
               
                k[i].enc= center[i].enc / count_group[i];
            }
			if(same_count == kcount){
                loop=false;
            }
            cout<<fixed<<setprecision(2);
			cout<<"("<<k[i].enc<<") ";
		}
        }cout<<endl;
    }//end of loop