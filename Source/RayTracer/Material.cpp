#include "Material.h"

bool Lambertian::Scatter(const ray_t& ray, const raycastHit_t& raycastHit, Color::color3_t& color, ray_t& scattered) const
{
    glm::vec3 target = raycastHit.point + raycastHit.normal + Random::randomInUnitSphere();
    glm::vec3 direction = glm::normalize(target - raycastHit.point);

    scattered = ray_t(raycastHit.point, direction);
    color = m_albedo;

    return true;
}

bool Metal::Scatter(const ray_t& ray, const raycastHit_t& raycastHit, glm::vec3& color, ray_t& scattered) const
{
    glm::vec3 reflected = glm::reflect(ray.direction, raycastHit.normal);

    // Set scattered ray from reflected ray + random point in sphere (fuzz = 0 no randomness, fuzz = 1 random reflected)
    // A mirror has a fuzz value of 0 and a diffused metal surface a higher value
    scattered = ray_t{ raycastHit.point, reflected + m_fuzz * Random::randomInUnitSphere() };
    color = m_albedo;

    // Make sure that reflected ray is going away from the surface normal (dot product > 0, angle between vectors < 90 degrees)
    return glm::dot(scattered.direction, raycastHit.normal) > 0;
}