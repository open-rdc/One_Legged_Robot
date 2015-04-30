#ifndef K_MEANS_FIVE_PARAMATER_H
#define K_MEANS_FIVE_PARAMATER_H

#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <time.h>
#include <algorithm>
#include <iomanip>


using namespace std;

#define NUM 100
#define cNUM 3
#define hNUM NUM/cNUM
#define pNUM 5

enum
{
	a1 = 0,
	t1,
	a2,
	t2,
	w
};

class kmeans
{
public:
	kmeans(void);
	void Clustering(void);				//クラスタリング
	void GetCluster(double c[cNUM][pNUM]);			//クラスタを取得

private:
	int GetRandom(int min, int max);	//乱数を生成
	void Init(void);					//初期化
	void DataInit(void);				//パラメータ初期化
	void RandomClusterInit(void);		//クラスタ初期化
	void CenterInit(void);				//クラスタ中心点を設定
	void Distance(void);				//距離を計算
	void GetCenter(void);				//中心点を取得
	void ChangeCluster(void);			//クラスタを切り替え
	
//	static bool InitFlg;				//初期化状態
	double pos[NUM][pNUM];		//パラメータ
	int cluster[cNUM];		//クラスタを保存
	double individual[NUM][pNUM];			//
	double distance[cNUM][NUM];	//
	double centerpoint[cNUM][pNUM];			//中心点
	double count_Group[cNUM];			//
	double min;							//
	int min_j;							//
	bool loop;							//繰返し用フラグ

};

#endif //K_MEANS_FIVE_PARAMATER_H