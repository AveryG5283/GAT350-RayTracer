#include <iostream>
#include "Renderer.h"
#include "Canvas.h"
#include "Random.h"
#include "Camera.h"
#include "Scene.h"
#include "Material.h"
#include "Ray.h"
#include "Sphere.h"
#include <memory>


int main(int argc, char* argv[])
{
	std::cout << "Hello World!";
	
	Renderer renderer;
	renderer.Initialize();
	renderer.CreateWindow("stinky", 400, 300);
	Canvas canvas(400, 300, renderer);

	float aspectRatio = canvas.GetSize().x / (float)canvas.GetSize().y;
	std::shared_ptr<Camera> camera = std::make_shared<Camera>(glm::vec3{ 0, 0, 1 }, glm::vec3{ 0, 0, 0 }, glm::vec3{ 0, 1, 0 }, 70.0f, aspectRatio);

	Scene scene(20);; // sky color could be set with the top and bottom color
	scene.SetCamera(camera);


	// create material
	auto lambertian = std::make_shared<Lambertian>(Color::color3_t{ 0, 0, 1 });
	auto metal = std::make_shared<Metal>(Color::color3_t{ 1, 1, 1 }, 0.0f);

	// create objects -> add to scene
	for (int i = 0; i < 10; i++)
	{
		std::shared_ptr<Material> material = (Random::random01() < 0.5f) ? std::dynamic_pointer_cast<Material>(lambertian) : std::dynamic_pointer_cast<Material>(metal);
		glm::vec3 position = glm::vec3{ Random::random(-5.0f, 5.0f), 0.5f, Random::random(-5.0f, 5.0f) };
		float radius = Random::random(0.1f, 0.5f);
		auto sphere = std::make_unique<Sphere>(position, radius, material);
		scene.AddObject(std::move(sphere));
	}

	bool quit = false;
	
	while (!quit)
	{
		SDL_Event event;
		SDL_PollEvent(&event);

		canvas.Clear({ 0, 0, 0, 1 });
		scene.Render(canvas);
		canvas.Update();

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