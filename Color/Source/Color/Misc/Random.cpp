#include "ColorPCH.h"
#include "Random.h"

namespace Color
{
	namespace RandomAlg
	{
		uint64_t Xorshift64(uint64_t& seed)
		{
			uint64_t num = seed;
			num ^= num << 13;
			num ^= num >> 7;
			num ^= num << 17;
			seed = num;

			return num;
		}
	}

	RandomGenerator::RandomGenerator(uint64_t seed)
		: m_Seed(seed)
	{
	}

	RandomGenerator RandomGenerator::SeededWithTime()
	{
		time_t rawtm;
		time(&rawtm);

		return RandomGenerator(rawtm);
	}

	bool RandomGenerator::BoolWithChance(int weight)
	{
		checkf(weight >= 0 && weight <= 100, "Weight out of range! It must be between 0 and 100.");

		// Even though the result may already be obvious given the value of "weight", this method is a random call.
		// Therefore, like every other random call, it must alter the m_Seed value. For this reason, we'll always use make a call to Range,
		// which makes a call to Generate that alters the seed.
		bool result = Range<int>(0, 100) <= weight;

		// Special case where weight = 0. Formula above won't work with this bad boy, so handle it seperately.
		if (weight == 0)
		{
			return false;
		}

		return result;
	}

	uint64_t RandomGenerator::Generate()
	{
		return RandomAlg::Xorshift64(m_Seed);
	}
}
