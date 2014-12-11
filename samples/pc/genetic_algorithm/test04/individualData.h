class individualData
{
public:
	double	gene;
	double	eva;
	int cluster;

	individualData(void);
	void setRandom(void);

	void setGene(double val);
	void setEva(double val);
	void setCluster(int num);

	double getGene(void);
	double getEva(void);
	int getCluster(void);

	~individualData(void);
};
