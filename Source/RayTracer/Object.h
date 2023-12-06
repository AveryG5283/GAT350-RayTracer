#pragma once
#include "Ray.h"
#include "Material.h"
#include <memory>

class Object
{
public:
    Object() = default;
    Object(std::shared_ptr<Material> material) :
        m_material{ material } {}

    virtual bool Hit(const ray_t& ray, float minDistance, float maxDistance, raycastHit_t& raycastHit) const = 0;

    Material* GetMaterial() const { return m_material.get(); }

protected:
    std::shared_ptr<Material> m_material;
};