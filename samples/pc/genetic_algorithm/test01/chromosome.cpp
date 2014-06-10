#include"chromosome.h"
#include<iostream>
#include<algorithm>


CChromosome::CChromosome()
{
	m_Fitness = -1;
}

void CChromosome::CalcFitness()
{
	m_Fitness = 0;
	for (vector<m_sGene>::iterator it=m_aGenes.begin(); it!=m_aGenes.end(); ++it)
		m_Fitness += it->m_Gene;
}

void CChromosome::Print()
{
	printf("Chromosome: ");
	for (vector<m_sGene>::iterator it=m_aGenes.begin(); it!=m_aGenes.end(); ++it)
		printf("%d", *it);
	printf("\tFitness: %d\n",m_Fitness);
}

void CChromosome::Print(bool Fitness)
{
	printf("Chromosome: ");
	for (vector<m_sGene>::iterator it=m_aGenes.begin(); it!=m_aGenes.end(); ++it)
		printf("%d", *it);
if(Fitness)
	printf("\tFitness: %d\n",m_Fitness);
else
	printf("\n");
}

void CChromosome::PrintSorted()
{
	std::sort(m_aGenes.begin(), m_aGenes.end());
	std::reverse(m_aGenes.begin(), m_aGenes.end());
	printf("Chromosome: ");
	for (vector<m_sGene>::iterator it=m_aGenes.begin(); it!=m_aGenes.end(); ++it)
		printf("%d", *it);
	printf("\tFitness: %d\n",m_Fitness);
}
