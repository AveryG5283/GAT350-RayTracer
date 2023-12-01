#include <iostream>
#include "Renderer.h"
#include "Canvas.h"
#include "Random.h"

int main(int argc, char* argv[])
{
	std::cout << "Hello World!";
	
	Renderer renderer;
	renderer.Initialize();
	renderer.CreateWindow("stinky", 400, 300);
	Canvas canvas(400, 300, renderer);

	bool quit = false;
	
	while (!quit)
	{
		SDL_Event event;
		SDL_PollEvent(&event);

		canvas.Clear({ 0, 0, 0, 1 });
		for (int i = 0; i < 1000; i++)
		{
			int randomX = rand() % 400;
			int randomY = rand() % 300;

			// Generate random RGB values
			float randomRed = static_cast<float>(rand()) / RAND_MAX;
			float randomGreen = static_cast<float>(rand()) / RAND_MAX;
			float randomBlue = static_cast<float>(rand()) / RAND_MAX;

			// Draw random points on the canvas with random RGB values
			canvas.DrawPoint({ randomX, randomY }, { randomRed, randomGreen, randomBlue, 1.0f });
		}
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