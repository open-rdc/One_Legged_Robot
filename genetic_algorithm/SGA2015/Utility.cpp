#include "Utility.h"

Utility::Utility():gen(GetTimeStamp())
{
}

unsigned long long Utility::GetTimeStamp()
{
	namespace pt = boost::posix_time;
	namespace gg = boost::gregorian;

	typedef boost::date_time::c_local_adjustor<pt::ptime> local_adj;

	pt::ptime epoch = local_adj::utc_to_local(pt::ptime(gg::date(1970, 1, 1)));
	pt::time_duration diff = pt::microsec_clock::local_time() - epoch;

	return diff.total_microseconds();
}

std::string Utility::GetTimeISOString()
{
	boost::posix_time::ptime today = boost::posix_time::second_clock::local_time();

	return boost::posix_time::to_iso_string(today);
}

void Utility::Random(int min, int max, int num)
{
	boost::random::uniform_int_distribution<> dist(min, max);

	for(int i=0; i<RANDOM_MAX; i++)
	{
		result[i][num] = dist(gen);
	}
}

int Utility::Random(int min, int max)
{
	boost::random::uniform_int_distribution<> dist(min, max);

	return dist(gen);
}

int Utility::GetRandom(int random_num, int parameter_num)
{
	return result[random_num][parameter_num];
}

unsigned long Utility::DecimalToBinary(std::bitset<32> decimal)
{
	std::bitset<32> value(decimal);
	
	return value.to_ulong();
}

std::bitset<32> Utility::BinaryToDecimal(std::bitset<32> binary)
{
	std::bitset<32> value(binary);

	return value;
}

/*!
 * @brief マスクを作成(0101010101)
 */
void Utility::SetMask()
{
	int bit_counter = 0;

	for(size_t i=0; i<mask.size(); i++)
	{
		if(bit_counter == 0)
		{
			mask.set(i, 1);
			bit_counter = 1;
		}
		else
		{
			bit_counter = 0;
		}
	}
}

/*!
 * @brief 一様交叉用のマスクを作成
 */
void Utility::SetMaskRandom()
{
	int bit_counter = 0;

	for(size_t i=0; i<mask_random.size(); i++)
	{
		bit_counter = Random(0, 1);
		mask_random.set(i, bit_counter == 1);
	}
}

std::bitset<32> Utility::GetMask()
{
	SetMask();

	return mask;
}

std::bitset<32> Utility::GetMaskRandom()
{
	SetMaskRandom();

	return mask_random;
}