static const int RANDOM_MAX = 100;
static const int TARGET_VALUE = 90;
static const int LOOP_COUNT = 10;
static const double RANKING_RATE = 0.2;
static const double INDIVIDUALS_NUMBER = RANDOM_MAX * RANKING_RATE;
static const double MUTATION_RATE = 0.01;
static const int MUTATION_POS = 6;

class individualData
{
private:
	double	gene;
	double	eva;
	int		cluster;
public:
	individualData(void);
	void	setRandom(void);

	void	setGene(double val);
	void	setEva(double val);
	void	setCluster(int num);

	double	getGene(void);
	double	getEva(void);
	int		getCluster(void);

	~individualData(void);
};