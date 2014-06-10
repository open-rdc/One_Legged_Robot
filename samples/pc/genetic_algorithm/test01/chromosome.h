#include<vector>
using namespace std;

struct m_sGene
{
    bool m_Gene;
	
	bool operator<(const m_sGene &rhs) const { return m_Gene < rhs.m_Gene; }
};

class CChromosome
{
public:
	CChromosome();
	int m_Fitness;
	vector<m_sGene> m_aGenes;
	void CalcFitness();
	void Print();
	void Print(bool);
	void PrintSorted();
	bool operator<(const CChromosome &rhs) const { return m_Fitness < rhs.m_Fitness; }
};
