#pragma once

#include "Core/Base.h"

#include <limits>

namespace Color
{
	namespace RandomAlg
	{
		uint64_t Xorshift64(uint64_t& seed);
	}

	class RandomGenerator
	{
	public:
		RandomGenerator() = default;
		RandomGenerator(const RandomGenerator&) = default;
		RandomGenerator& operator=(const RandomGenerator&) = default;
		RandomGenerator(uint64_t seed);

		// Creates a RandomGenerator instance with the seed being the localtime at the moment of creation.
		static RandomGenerator SeededWithTime();

		template <typename T, std::enable_if_t<std::is_integral_v<T>, int> = 0>
		T Range(T min = std::numeric_limits<T>::min(), T max = std::numeric_limits<T>::max())
		{
			// Special case where max as the limit of given type is requested. Unfortunately, we cannot work with the full range.
			// We'll have to compromise on the range by 1.
			if (max == std::numeric_limits<T>::max())
			{
				max--;
			}

			return Generate() % (max + 1 - min) + min;
		}
		
		template <typename T, std::enable_if_t<std::is_floating_point_v<T>, int> = 0>
		T Range(T min = std::numeric_limits<T>::min(), T max = std::numeric_limits<T>::max())
		{
			return ((max - min) * ((T) Generate() / std::numeric_limits<uint64_t>::max())) + min;
		}

		bool        Bool()       { return static_cast<bool>(Range<uint8_t>(0, 1)); }
		int8_t      Int8()       { return Range<int8_t>(); }
		int16_t     Int16()      { return Range<int16_t>(); }
		int32_t     Int32()      { return Range<int32_t>(); }
		int64_t     Int64()      { return Range<int64_t>(); }

		uint8_t     UInt8()      { return Range<uint8_t>(); }
		uint16_t    UInt16()     { return Range<uint16_t>(); }
		uint32_t    UInt32()     { return Range<uint32_t>(); }
		uint64_t    UInt64()     { return Range<uint64_t>(); }

		float       Float()      { return Range<float>(); }
		double      Double()     { return Range<double>(); }
		long double LongDouble() { return Range<long double>(); }

		// Generates a random boolean value with luck in which the greater weight is, the more likely that the value will be true.
		// weight must be in range: 0 to 100.
		bool BoolWithChance(int weight);
	private:
		uint64_t Generate();
	private:
		uint64_t m_Seed = 0;
	};
}
