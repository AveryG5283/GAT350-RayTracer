#include <iostream>
#include "Renderer.h"
#include "Canvas.h"
#include "Random.h"
#include "Camera.h"
#include "Scene.h"
#include "Material.h"
#include "Ray.h"
#include "Sphere.h"
#include "Plane.h"
#include "Triangle.h"
#include "Mesh.h"
#include <memory>


int main(int argc, char* argv[])
{
	std::cout << "Hello World!";
	
	const int width = 400;
	const int height = 300;
	const int samples = 20;
	const int depth = 5;

	Renderer renderer;
	renderer.Initialize();
	renderer.CreateWindow("Ray Tracer", width, height);
	Canvas canvas(width, height, renderer);

	float aspectRatio = canvas.GetSize().x / (float)canvas.GetSize().y;
	std::shared_ptr<Camera> camera = std::make_shared<Camera>(glm::vec3{ 0, 1, 10 }, glm::vec3{ 0, 0, 0 }, glm::vec3{ 0, 1, 0 }, 20.0f, aspectRatio);
	Scene scene(8, glm::vec3{ 1.0f }, glm::vec3{ 0.5f, 0.7f, 1.0f });
	scene.SetCamera(camera);
	
	InitScene01(scene, canvas);

	// render scene 
	canvas.Clear({ 0, 0, 0, 1 });
	scene.Render(canvas, samples, depth);
	canvas.Update();
	bool quit = false;
	
	while (!quit)
	{
		SDL_Event event;
		SDL_PollEvent(&event);

		/*
		canvas.Clear({ 0, 0, 0, 1 });
		scene.Render(canvas);
		canvas.Update();
		*/

		renderer.PresentCanvas(canvas);

		switch (event.type)
		{
		case SDL_QUIT:
			quit = true;
			break;
		}
	}

	renderer.Shutdown();

	return 0;
}

void InitScene01(Scene& scene, const Canvas& canvas)
{
	float aspectRatio = canvas.GetSize().x / canvas.GetSize().y;
	std::shared_ptr<Camera> camera = std::make_shared<Camera>(glm::vec3{ 0, 2, 10 }, glm::vec3{ 0, 1, 0 }, glm::vec3{ 0, 1, 0 }, 20.0f, aspectRatio);
	scene.SetCamera(camera);

	// create objects -> add to scene
	for (int x = -10; x < 10; x++)
	{
		for (int z = -10; z < 10; z++)
		{
			std::shared_ptr<Material> material;

			// create random material
			float r = Random::random01();
			if (r < 0.3f)		material = std::make_shared<Lambertian>(glm::rgbColor(glm::vec3{ Random::random(0, 360), 1.0f, 1.0f }));
			else if (r < 0.6f)	material = std::make_shared<Metal>(Color::color3_t{ Random::random(0.5f, 1.0f) }, Random::random(0, 0.5f));
			else if (r < 0.9f)	material = std::make_shared<Dielectric>(Color::color3_t{ 1.0f }, Random::random(1.1f, 2));
			else				material = std::make_shared<Emissive>(glm::rgbColor(glm::vec3{ Random::random(0, 360), 1.0f, 1.0f }), 5.0f);

			// set random sphere radius
			float radius = Random::random(0.2f, 0.3f);
			// create sphere using random radius and material
			auto sphere = std::make_unique<Sphere>(glm::vec3{ x + Random::random(-0.5f, 0.5f), radius, z + Random::random(-0.5f, 0.5f) }, radius, material);
			// add sphere to the scene
			scene.AddObject(std::move(sphere));
		}
	}

	auto plane = std::make_unique<Plane>(glm::vec3{ 0, 0, 0 }, glm::vec3{ 0, 1, 0 }, std::make_shared<Lambertian>(Color::color3_t{ 0.2f }));
	scene.AddObject(std::move(plane));
}

void InitScene02(Scene& scene, const Canvas& canvas)
{
	float aspectRatio = canvas.GetSize().x / canvas.GetSize().y;
	std::shared_ptr<Camera> camera = std::make_shared<Camera>(glm::vec3{ 0, 2, 10 }, glm::vec3{ 0, 1, 0 }, glm::vec3{ 0, 1, 0 }, 20.0f, aspectRatio);
	scene.SetCamera(camera);

	//auto triangle = std::make_unique<Triangle>(glm::vec3{ -1, 0, 0 }, glm::vec3{ 1, 0, 0 }, glm::vec3{ 0, 2, 0 }, std::make_shared<Lambertian>(color3_t{ 1, 0, 0 }));
	//scene.AddObject(std::move(triangle));

	auto plane = std::make_unique<Plane>(glm::vec3{ 0, 0, 0 }, glm::vec3{ 0, 1, 0 }, std::make_shared<Lambertian>(Color::color3_t{ 0.2f }));
	scene.AddObject(std::move(plane));

	auto mesh = std::make_unique<Mesh>(std::make_shared<Lambertian>(Color::color3_t{ 0, 0, 1 }));
	mesh->Load("models/cube.obj", glm::vec3{ 0, 0.5f, 0 }, glm::vec3{ 0, 45, 0 });
	scene.AddObject(std::move(mesh));
}