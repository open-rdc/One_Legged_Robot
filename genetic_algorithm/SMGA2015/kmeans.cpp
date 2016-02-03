#include <math.h>
#include "kmeans.h"
#include "parameter.h"

Kmeans::Kmeans(void)
{
}

/*!
 * @brief 初期化
 *
 * @param[in] data_no データの数
 * @param[in] cluster_no クラスタの数
 * @param[in] parameter_no パラメータの数
 *
 */
void Kmeans::Init(int data_no, int cluseter_no, int parameter_no)
{
	this->data_no = data_no;
	this->cluster_no = cluseter_no;
	this->parameter_no = parameter_no;

	data.resize(data_no * parameter_no, 0);
	id.resize(data_no, 0);
	center2.resize(cluster_no * parameter_no, 0);
}

/*!
 * @brief データのセット
 * @return true:成功，false:失敗
 */
bool Kmeans::SetData(vector<double> data){
	if (data.size() != data_no * parameter_no){
		cout << "SetData: check the number of data\n" << endl;
		return false;
	}
	this->data = data;
	return true;
}

/*!
 * @brief 距離の取得
 * @param[in] a 位置ベクトル
 * @param[in] b 位置ベクトル
 * @return 距離
 */
double Kmeans::GetDistance(vector<double>a, vector<double>b)
{
	if (a.size() != b.size()) return 0.0;
	
	int dim = a.size();
	double val = 0.0;
	for(int i = 0; i < dim; i ++){
		val += fabs(a[i] - b[i]);
	}
	return pow(val, 1.0/dim);
}

/*!
 * @brief 個体のデータを取得する
 * @param[in] id ID番号 (0 - (data_no-1))
 * @return 位置ベクトル
 */
vector<double> Kmeans::GetVector(vector<double> a, int id){
	vector<double> ret(parameter_no);
	for(int i = 0; i < parameter_no; i ++){
		ret[i] = a[id * parameter_no + i];
	}
	return ret;
}

/*
 * @brief K-meansの繰り返し処理部
 * 徐々に重心と属する個体を計算していく
 */
void Kmeans::ReClustering(void)
{
	vector<double> center_t(cluster_no * parameter_no, 0.0);
	vector<int> num(parameter_no, 0);

	for(int i = 0; i < data_no; i++){
		vector<double> pickup_data = GetVector(data, i);
		min = GetDistance(pickup_data, GetVector(center2, 0));
        min_j = 0;
 
		for(int j = 1; j < cluster_no; j++){
			double dist = GetDistance(pickup_data, GetVector(center2, j));
			if(min > dist){
				min   = dist;
				min_j = j;
			}
        }
		num[min_j] ++;
		id[i] = min_j;
		for(int j = 0;j < parameter_no; j ++){
			center_t[parameter_no * min_j + j] += pickup_data[j];
		}
    }
	for(int i = 0; i < cluster_no; i ++){
		for(int j = 0; j < parameter_no; j ++){
			center_t[parameter_no * i + j] /= num[i];
		}
	}
}


void Kmeans::Clustering(void)
{
	vector<double> pre_center(cluster_no * parameter_no, 0);
	double distance = 1.0;
	while(distance == 0.0)
	{
		copy(center2.begin(), center2.end(), pre_center.begin());
		ReClustering();
		distance = 0.0;
		for(int i = 0; i < parameter_no; i ++){
			distance += GetDistance(center2, pre_center);
		}
	}
}

/*!
 * @brief クラスタに属するデータを取得
 * 
 * @param[out] c クラスタに属するデータ
 * @param[in] clusterNum クラスタの番号
 */
void Kmeans::GetCluster(int c[RANDOM_MAX][PARAMETER_NUM], int clusterNum)
{
	int n = 0;
	for(int i = 0; i < ClusterParameter[clusterNum]; i++)
	{
		if (id[i] = clusterNum){
			for(int j = 0; j < parameter_no; j++)
			{
				c[n][j] = (int)data[parameter_no * i + j];
			}
			n ++;
		}
	}
}

/*
 * @brief クラスタ情報の表示
 */
void Kmeans::DisplayClusters()
{
	for(int i = 0; i < cluster_no; i++)
	{
		cout << "Disp Cluster Num:" << i+1 << endl;
		cout << "Center Point (" ;

		ofs << "Disp Cluster Num:" << i+1 << endl;
		ofs << "Center Point ";

		for(int j = 0; j < parameter_no; j++)
		{
			ofs << ",";
			cout << " " << (int)center2[parameter_no * i + j] << " ";
			ofs << " " << (int)center2[parameter_no * i + j] << " ";
		}
		ofs << endl << endl;
		cout << ")" << endl << endl;
		for(int j = 0; j < data_no; j++)
		{
			if (id[j] == i){
				cout << "No." << j+1 << "("  ;
				ofs << "No." << j+1 << " ";
				for(int k = 0; k < parameter_no; k++)
				{
					cout << " " << (int)data[parameter_no * j + k] << " ";
					ofs << "," << (int)data[parameter_no * j + k];
				}
				ofs << endl;
				cout << ")" << endl;
			}
		}
		cout << endl;
		ofs << endl;
	}
	cout << endl;
	ofs << endl;
}

/*!
 * @brief パラメータの表示
 */
void Kmeans::DisplayParameter()
{
	for(int i = 0; i < data_no; i++)
	{
		cout << "No." << i + 1 << "(";
		for(int j = 0; j < parameter_no; j++)
		{
			cout << " " << data[parameter_no * i + j] << " ";
		}
		cout << ")" << endl;
	}
	cout << endl;
}

/*
void Kmeans::ChangePos(int c[RANDOM_MAX][PARAMETER_NUM],int clusterNum)
{
	for(int i=0;i<ClusterParameter[clusterNum];i++)
	{
		for(int j=0;j<PARAMETER_NUM;j++)
		{
			pos[cluster[clusterNum][i]][j] = (double)c[i][j];
		}
	}
}

void Kmeans::ChangeCenterPoint(int CenterPointNum,int clusterNum){
	center[clusterNum] = CenterPointNum;
}
*/