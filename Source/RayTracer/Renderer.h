#pragma once
#include <SDL.h>
#include <iostream>

class Renderer
{
public:
	Renderer() = default;
	bool Initialize();
	void Shutdown();
	bool CreateWindow(const std::string& title, int width, int height);
	void PresentCanvas(const class Canvas& canvas);
	SDL_Renderer* m_renderer = nullptr;

	friend class Canvas;
private:
	SDL_Window* m_window = nullptr;
	
};