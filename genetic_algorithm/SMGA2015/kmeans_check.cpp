#include "kmeans.h"

int main(void)
{
	Kmeans kmeans;
	int data_no = 100, cluster_no = 3, parameter_no = 2;
	kmeans.Init(data_no, cluster_no, parameter_no);
	vector<double> data(data_no * parameter_no);
	
	for(int i = 0; i < data_no * parameter_no; i ++)
	{
		data[i] = rand() % 100;
	}

	ofstream ofs;
	ofs.open("result.csv");

	kmeans.SetData(data);
	cout << kmeans << endl;
	ofs << kmeans << endl;

	kmeans.Clustering();
	cout << kmeans << endl;
	ofs << kmeans << endl;

	ofs.close();

	getchar();
}