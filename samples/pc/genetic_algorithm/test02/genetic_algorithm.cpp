#include <iostream>
#include <boost/random.hpp>
#include <boost/date_time.hpp>
#include <boost/date_time/c_local_time_adjustor.hpp>
#include "parameter.h"

__int64 GetTimeStamp()
{
	namespace pt = boost::posix_time;
	namespace gg = boost::gregorian;

	typedef boost::date_time::c_local_adjustor<pt::ptime> local_adj;

	auto epoch = local_adj::utc_to_local(pt::ptime(gg::date(1970, 1, 1)));
	auto diff = pt::microsec_clock::local_time() - epoch;

	return diff.total_microseconds();
}

void Random(int min, int max, int *result, size_t n)
{
	boost::random::mt19937 gen(GetTimeStamp());
	boost::random::uniform_int_distribution<> dist(min, max);

	for(int i=0; i<RANDOM_MAX/2; i++)
	{
		result[i] = dist(gen);
	}
}

void Initialize(std::string *gene, size_t n)
{
	int angle[RANDOM_MAX/2];
	int time[RANDOM_MAX/2];

	Random(-90, 90, angle, sizeof(angle) / sizeof(angle[0]));
	Random(0, 1000, time, sizeof(time) / sizeof(time[0]));

	for(int i=0; i<RANDOM_MAX / GENE_LENGTH; i++)
	{
		for(int j=0; j<GENE_LENGTH/2; j++)
		{
			gene[i] += std::to_string(angle[i*2 + j]);
			gene[i] += ",";
			gene[i] += std::to_string(time[i*2 + j]);
			gene[i] += ",";
		}
		gene[i].erase(gene[i].end() - 1);
		gene[i] += "\n";
	}
}

int main()
{
	std::string gene[RANDOM_MAX / GENE_LENGTH];
	Initialize(gene, sizeof(gene) / sizeof(gene[0]));

	for(int i=0; i<RANDOM_MAX / GENE_LENGTH; i++)
	{
		std::cout << "gene[" << i << "]:" << gene[i];
	}

	return 0;
}