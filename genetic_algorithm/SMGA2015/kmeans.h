#ifndef K_MEANS__H
#define K_MEANS__H

#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <time.h>
#include <algorithm>
#include <iomanip>
#include <vector>
#include "parameter.h"
#include "FileManager.h"


using namespace std;

enum
{
	a1 = 0,
	a2,
	w
};

class Kmeans
{
public:

//	void ChangePos(int c[RANDOM_MAX][PARAMETER_NUM],int clusterNum);
//	void ChangeCenterPoint(int CenterPointNum,int clusterNum);
	int ClusterParameter[CLUSTER_NUM];

private:
	bool LoadFile(void);
	bool LoadInitFile(void);
	
//	static bool InitFlg;				//初期化状態
	double pos[RANDOM_MAX][PARAMETER_NUM];		//パラメータ
	int center[CLUSTER_NUM];		//クラスタを保存
	int cluster[CLUSTER_NUM][RANDOM_MAX];
	double individual[RANDOM_MAX][PARAMETER_NUM];			//
	double distance[CLUSTER_NUM][RANDOM_MAX];	//
	double centerpoint[CLUSTER_NUM][PARAMETER_NUM];			//中心点
	double count_Group[CLUSTER_NUM];			//
	double min;							//
	int min_j;							//
	bool loop;							//繰返し用フラグ
	FileManager fmp;						//再利用目的データ
	ofstream ofs;

public:
	Kmeans(void);
	void Init(int data_no, int cluseter_no, int parameter_no);
	bool SetData(vector<double> data);
	void Clustering(void);				//クラスタリング
	void GetCluster(int c[RANDOM_MAX][PARAMETER_NUM],int clusterNum);

private:
	void ReClustering(void);				//中心点を取得
	double GetDistance(vector<double>a, vector<double>b);	//距離を計算
	vector<double> GetVector(vector<double> a, int id);
	void DisplayClusters(void);			//完成したクラスターを表示
	void DisplayParameter(void);

	int data_no;				// データ数 
	int cluster_no;				// クラスタ数
	int parameter_no;			// パラメータ数（次元）
	vector<double> data;		// データ(double型とする)
	vector<double> id;			// データが属するクラスタ番号
	vector<double> center2;		// 重心の値
};

#endif //K_MEANS_H