#include <ctime>
#include<iostream>
#include<algorithm>
#include"chromosome.h"
using namespace std;

vector<CChromosome> g_Chromosomes;
int g_Count, g_Genes;

class CChromosome Create()
{
	CChromosome x;
	x.	m_Fitness = 0;
	for(int i = 0; i < g_Genes; ++i)
	{
		m_sGene y;
		y.m_Gene = (rand()+rand()*rand()) % 2;
		x.m_aGenes.push_back(y);
	}
	x.CalcFitness();
	return x;
}

void Print()
{
	for(vector<CChromosome>::iterator it = g_Chromosomes.begin(); it != g_Chromosomes.end(); it++)
	{
		it->Print();
	}
}

void Print(bool Type)
{
	int num = 0;
	for(vector<CChromosome>::iterator it = g_Chromosomes.begin(); it != g_Chromosomes.end(); it++)
	{
		if(Type)
		{
			cout << ++num;
			cout << ".\t";
		}
		it->Print(Type);
	}
}

void Sort()
{
	for(vector<CChromosome>::iterator it = g_Chromosomes.begin(); it != g_Chromosomes.end(); it++)
	{
		it->CalcFitness();
	}
	sort(g_Chromosomes.begin(), g_Chromosomes.end());
	reverse(g_Chromosomes.begin(), g_Chromosomes.end());
}

int Average()
{
	int Temp = 0;
	for(vector<CChromosome>::iterator it = g_Chromosomes.begin(); it != g_Chromosomes.end(); it++)
	{
		Temp += it->m_Fitness;
	}
	if(Temp/g_Chromosomes.size() > g_Genes/2)
		return Temp/g_Chromosomes.size();
	else
		return Temp/g_Chromosomes.size() + 1;
}

void CrossOver()
{
	int From = 0, Ave = Average(), Genes;
	bool Even = (g_Genes % 2) == 0;
	Genes = g_Genes/2;
	cout << "Average = " << Ave << "\n";
	for(vector<CChromosome>::iterator it = g_Chromosomes.begin(); it != g_Chromosomes.end(); it++)
	{
		if(it->m_Fitness <= Ave)
			break;
		From++;
	}
	int Count = 0;
	for(int i = From; i < g_Chromosomes.size()-1; ++i)
	{
		int Size = g_Chromosomes[i+1].m_aGenes.size();
		for(int j = 0; j < Genes; ++j)
		{
			int Elm = Size - (Genes - j);
			bool Temp = g_Chromosomes[i].m_aGenes[j].m_Gene;
			g_Chromosomes[i].m_aGenes[j].m_Gene = g_Chromosomes[i+1].m_aGenes[Elm].m_Gene;
			g_Chromosomes[i+1].m_aGenes[Elm].m_Gene = Temp;
		}
	}
}

void Mutation()
{
	if(g_Chromosomes[g_Count - 1].m_Fitness == g_Genes)
		return;
	int From = 0, Ave = Average(), Chromosome, Limit;
	for(vector<CChromosome>::iterator it = g_Chromosomes.begin(); it != g_Chromosomes.end(); it++)
	{
		if(it->m_Fitness <= Ave)
			break;
		From++;
	}
	bool Answer;
	do
	{
	Limit = g_Chromosomes.size() - From;
	Chromosome = (g_Chromosomes.size() - (rand() % Limit)) - 1;
	Limit = (rand() % g_Chromosomes[Chromosome].m_aGenes.size()) - 1;
	if(Limit < 0)
		Limit = 0;
	Answer = g_Chromosomes[Chromosome].m_aGenes[Limit].m_Gene;
	}
	while(Answer);
	g_Chromosomes[Chromosome].m_aGenes[Limit].m_Gene = true;
}

void Clear()
{
	g_Chromosomes.clear();
}

int main()
{
	srand( (unsigned)time( NULL ) );
	while(true)
	{
		cout << "How many Chromosomes do you want ?\n";
		cin >> g_Count;
		cout << "How many genes do you want in each Chromosome ?\n";
		cin >> g_Genes;
		for(int i = 0; i < g_Count; ++i)
			g_Chromosomes.push_back(Create());
		int Rotations;
		cout << "How many Cycles ?\n";
		cin >> Rotations;
		cout << "Chromosomes:\n";
		Print();
		cout << "Ranks:\n";
		Sort();
		Print(true);
		for(int z = 0; z < Rotations; ++z)
		{
			CrossOver();
			cout << "After CrossOver:\n";
			Print(false);
			Mutation();
			cout << "After Mutation:\n";
			Print(false);
			cout << "Ranks:\n";
			Print(true);
			Sort();
			cout << "Press Enter (Return) to Reload\n";
		}
		cout << endl;
		cin.get();
		Clear();
	}
	return 0;
}
