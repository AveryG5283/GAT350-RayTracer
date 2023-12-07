#include "Plane.h"
#include "MathUtils.h"

bool Plane::Hit(const ray_t& ray, float minDistance, float maxDistance, raycastHit_t& raycastHit) const
{
	float denominator = MathUtils::dot(ray.direction, m_normal);
	if (MathUtils::approximately(denominator, 0))
	{
		return false;
	}

	float t = glm::dot(m_center - ray.origin, m_normal) / denominator;

	if (t < 0)
	{
		return false;
	}

	if (t > minDistance && t < maxDistance)
	{
		return true;
	}

	return false;
}
