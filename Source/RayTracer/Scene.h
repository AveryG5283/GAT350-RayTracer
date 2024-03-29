#pragma once
#include "Camera.h"
#include "Ray.h"
#include "Color.h"
#include "Object.h"
#include <memory>
#include <vector>

class Scene
{
public:
	Scene() = default;
	//Scene(int depth = 5) : m_depth{ depth } {}
	Scene(int depth, const Color::color3_t& topColor, const Color::color3_t& bottomColor) :
		//m_depth{ depth },
		m_topColor{ topColor },
		m_bottomColor{ bottomColor }
	{}

	void Render(class Canvas& canvas, int numSamples, int depth);
	Color::color3_t Trace(const ray_t& ray, float minDistance, float maxDistance, raycastHit_t& raycastHit, int depth);
	void AddObject(std::unique_ptr<Object> object) { m_objects.push_back(std::move(object)); }

	void SetCamera(std::shared_ptr<Camera> camera) { m_camera = camera; }

private:
	std::shared_ptr<Camera> m_camera;

	Color::color3_t m_topColor{ 0 };
	Color::color3_t m_bottomColor{ 1 };
	//int m_depth{ 8 };

	std::vector<std::unique_ptr<Object>> m_objects;
};