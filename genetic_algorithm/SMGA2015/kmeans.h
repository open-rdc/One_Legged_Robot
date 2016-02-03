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
	int ClusterParameter[CLUSTER_NUM];

private:
	ofstream ofs;

public:
	Kmeans(void);
	void Init(int data_no, int cluseter_no, int parameter_no);
	bool SetData(vector<double> data);
	void Clustering(void);				//クラスタリング
	void GetCluster(int c[RANDOM_MAX][PARAMETER_NUM],int clusterNum);
	friend ostream &operator<<(ostream &out, const Kmeans &kmeans);

private:
	void calcCenter();
	void ReClustering(void);				//中心点を取得
	double GetDistance(vector<double>a, vector<double>b);	//距離を計算
	vector<double> GetVector(vector<double> a, int id);
	void DisplayClusters(void);			//完成したクラスターを表示

	int data_no;				// データ数 
	int cluster_no;				// クラスタ数
	int parameter_no;			// パラメータ数（次元）
	vector<double> data;		// データ(double型とする)
	vector<double> id;			// データが属するクラスタ番号
	vector<double> center2;		// 重心の値
};

#endif //K_MEANS_H