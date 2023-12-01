#pragma once
#include <cstdlib>
#include <algorithm>

class Random
{
public:
	inline void seedRandom(unsigned int seed)
	{
		std::srand(seed);
	}

	inline float random01()
	{
		return static_cast<float>(std::rand()) / RAND_MAX;
	}

	inline float random(float min, float max)
	{
		// swaps if min is bigger than max
		if (min > max) {
			std::swap(min, max);
		}

		return min + (max - min) * random01();
	}
};
