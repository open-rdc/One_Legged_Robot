#include<iostream>
#include<iomanip>
#include<algorithm>
#include<vector>
#include<string>

using namespace std;

#define kcount 10
#define data 100

class pos{
public:
	double s1;
	double t1;
	double s2;
	double t2;
	double t3;
};

int main()
{
	pos* k=new pos[kcount];
	pos* center=new pos[kcount];

	double count_group[kcount]={};

	vector<pos>datas;
	vector<double> distance[kcount];

	//個体をランダムに生成する
	for(int i=0; i<data; i++)
	{
		pos tmp;
		tmp.s1=(double)(rand()%100);
		tmp.t1=(double)(rand()%100);
		tmp.s2=(double)(rand()%100);
		tmp.t2=(double)(rand()%100);
		tmp.t3=(double)(rand()%100);
		cout<<"("<<tmp.s1<<","<<tmp.t1<<","<<tmp.s2<<","<<tmp.t2<<","<<tmp.t2<<","<<tmp.t3<<")"<<endl;
		datas.push_back(tmp);
	};

	//クラスタ初期化
	for(int i=0; i<kcount; i++)
    {
        k[i] = datas[i];
		center[i].s1 = datas[i].s1;
		center[i].t1=datas[i].t1;
		center[i].s2=datas[i].s2;
		center[i].t2=datas[i].t2;
		center[i].t3=datas[i].t3;
		distance[i].resize(data);
    }

	bool loop=true;
	while(loop){//k位置は次の位置ですべて同じである場合
		
		//センターポイント初期化
		for(int i=0; i<kcount; i++)
		{
			center[i].s1=0;
			center[i].t1=0;
			center[i].s2=0;
			center[i].t2=0;
			center[i].t3=0;
			count_group[i]=0;
		};

		//距離の計算
		for(int i=0;i<datas.size(); i++){
			for(int j=0;j<kcount; j++){
				double tmp_distance = sqrt ( pow( k[j].s1 - datas[i].s1, 2)+
					                         pow( k[j].t1 - datas[i].t1, 2)+
											 pow( k[j].s2 - datas[i].s2, 2)+
											 pow( k[j].t2 - datas[i].t2, 2)+
											 pow( k[j].t3 - datas[i].t3, 2));
                distance[j][i] = tmp_distance;
            }
        };

		//センターポイントを取る
		for(int i=0;i<datas.size(); i++){
            double min = distance[0][i];
            int min_j = 0;
 
			for(int j=1;j<kcount; j++){
                if(min > distance[j][i]){
                    min = distance[j][i];
                    min_j = j;
                }
            }
			center[ min_j ].s1 += datas[i].s1;
			center[ min_j ].t1 += datas[i].t1;
			center[ min_j ].s2 += datas[i].s2;
			center[ min_j ].t2 += datas[i].t2;
			center[ min_j ].t3 += datas[i].t3;
			count_group[min_j]++;
        }
 
		//クラスタを引き換える
        int same_count = 0;
		for(int i=0;i<kcount; i++){
           
 
			if(count_group[i] != 0){
				if((center[i].s1 / count_group[i]) == k[i].s1 
					&& (center[i].t1 / count_group[i]) == k[i].t1
					&& (center[i].s2 / count_group[i]) == k[i].s2
					&& (center[i].t2 / count_group[i]) == k[i].t2
					&& (center[i].t3 / count_group[i]) == k[i].t3)
                        same_count ++;
               
				k[i].s1 = center[i].s1 / count_group[i];
				k[i].t1 = center[i].t1 / count_group[i];
				k[i].s2 = center[i].s2 / count_group[i];
				k[i].t2 = center[i].t2 / count_group[i];
				k[i].t3 = center[i].t3 / count_group[i];
            }
			if(same_count == kcount){
                loop=false;
            }
            cout<<fixed<<setprecision(2);
			cout<<"("<<k[i].s1<<","<<k[i].t1<<","<<k[i].s2<<","<<k[i].t2<<","<<k[i].t3<<") "<<endl;
        }cout<<endl;
    }
}