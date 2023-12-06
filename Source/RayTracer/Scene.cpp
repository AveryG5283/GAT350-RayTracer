#include "Scene.h"
#include "Canvas.h"
#include "MathUtils.h"


void Scene::Render(Canvas& canvas)
{
    // Cast ray for each point (pixel) on the canvas
    for (int y = 0; y < canvas.GetSize().y; y++)
    {
        for (int x = 0; x < canvas.GetSize().x; x++)
        {
            // Create vec2 pixel from canvas x,y
            glm::vec2 pixel = glm::vec2{ x, y };

            // Get normalized (0 - 1) point coordinates from pixel
            glm::vec2 point = pixel / glm::vec2(canvas.GetSize());
            // Flip y
            point.y = 1.0f - point.y;

            // Create ray from camera
            ray_t ray = m_camera->GetRay(point);

            // Cast ray into scene
            raycastHit_t raycastHit;
            Color::color3_t color = Trace(ray, 0, 100, raycastHit, 5);

            // Draw color to canvas point (pixel)
            canvas.DrawPoint(glm::ivec2(x, y), Color::color4_t(color, 1));
        }
    }
}

Color::color3_t Scene::Trace(const ray_t& ray, float minDistance, float maxDistance, raycastHit_t& raycastHit, int depth)
{
    bool rayHit = false;
    float closestDistance = maxDistance;

    // check if scene objects are hit by the ray
    for (const auto& object : m_objects)
    {
        // when checking objects don't include objects farther than closest hit (starts at max distance)
        if (object->Hit(ray, minDistance, closestDistance, raycastHit))
        {
            rayHit = true;
            // set closest distance to the raycast hit distance (only hit objects closer than closest distance)
            closestDistance = raycastHit.distance;
        }
    }

    // if ray hit object, scatter (bounce) ray and check for the next hit
    // if ray hit object, scatter (bounce) ray and check for next hit
    if (rayHit)
    {
        ray_t scattered;
        Color::color3_t color;

        // check if maximum depth (number of bounces) is reached, get color from material and scattered ray
        if (depth > 0 && raycastHit.material->Scatter(ray, raycastHit, color, scattered))
        {
            // recursive function, call self and modulate (multiply) colors of depth bounces
            return color * Trace(scattered, minDistance, maxDistance, raycastHit, depth - 1);
        }
        else
        {
            // reached maximum depth of bounces (color is black)
            return Color::color3_t{ 0, 0, 0 };
        }
    }
    // if ray not hit, return scene sky color
    glm::vec3 direction = glm::normalize(ray.direction);
    float t = 0.5f * (direction.y + 1.0f); // direction.y (-1 <-> 1) => (0 <-> 1)
    Color::color3_t color = MathUtils::lerp(m_bottomColor, m_topColor, t);

    return color;
}