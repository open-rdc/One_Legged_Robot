#ifndef K_MEANS_THREE_PARAMATER_H
#define K_MEANS_THREE_PARAMATER_H

#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <time.h>
#include <algorithm>
#include <iomanip>
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
	Kmeans(void);
	void Clustering(void);				//クラスタリング
	void GetCenterPos(int c[CLUSTER_NUM][PARAMETER_NUM]);			//クラスタの中心点のパラメータを取得
	void GetCluster(int c[CLUST_PARAM_NUM][PARAMETER_NUM],int clusterNum);
	void Init(void);
	void ChangePos(int c[CLUST_PARAM_NUM][PARAMETER_NUM],int clusterNum);
	void ChangeCenterPoint(int CenterPointNum,int clusterNum);

private:
	int GetRandom(int min, int max);	//乱数を生成				//初期化
	void DataInit(void);				//パラメータ初期化
	void RandomClusterInit(void);		//クラスタ初期化
	void CenterInit(void);				//クラスタ中心点を設定
	void Distance(void);				//距離を計算
	void GetCenter(void);				//中心点を取得
	void ChangeCluster(void);			//クラスタを切り替え
	void DisplayClusters(void);			//完成したクラスターを表示
	void DisplayParameter(void);
	void SaveParameter(void);
	bool LoadFile(void);
	bool LoadInitFile(void);
	
//	static bool InitFlg;				//初期化状態
	double pos[RANDOM_MAX][PARAMETER_NUM];		//パラメータ
	int center[CLUSTER_NUM];		//クラスタを保存
	int cluster[CLUSTER_NUM][CLUST_PARAM_NUM];
	double individual[RANDOM_MAX][PARAMETER_NUM];			//
	double distance[CLUSTER_NUM][RANDOM_MAX];	//
	double centerpoint[CLUSTER_NUM][PARAMETER_NUM];			//中心点
	double count_Group[CLUSTER_NUM];			//
	double min;							//
	int min_j;							//
	bool loop;							//繰返し用フラグ
	FileManager fmp;						//再利用目的データ
	ofstream ofs;

};

#endif //K_MEANS_THREE_PARAMATER_H