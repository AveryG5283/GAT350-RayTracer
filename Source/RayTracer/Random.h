#pragma once
#include <cstdlib>
#include <algorithm>
#include <glm/glm.hpp>
#include <glm/gtx/norm.hpp>

class Random
{
public:
	static inline void seedRandom(unsigned int seed)
	{
		std::srand(seed);
	}

	static inline float random01()
	{
		return static_cast<float>(std::rand()) / RAND_MAX;
	}

	static inline float random(float min, float max)
	{
		// swaps if min is bigger than max
		if (min > max) {
			std::swap(min, max);
		}

		return min + (max - min) * random01();
	}

	static inline glm::vec3 random(const glm::vec3& min, const glm::vec3& max)
	{
		// Returns a random vector within the specified range
		return glm::vec3(
			random(min.x, max.x),
			random(min.y, max.y),
			random(min.z, max.z)
		);
	}
	
	static inline glm::vec3 randomInUnitSphere()
	{
		glm::vec3 v;
		// Generate random vectors between -1 and 1, return vector if length is less than 1
		do
		{
			v = glm::vec3(
				random(-1.0f, 1.0f),
				random(-1.0f, 1.0f),
				random(-1.0f, 1.0f)
			);
		} while (glm::length2(v) >= 1.0f);

		return v;
	}
};
