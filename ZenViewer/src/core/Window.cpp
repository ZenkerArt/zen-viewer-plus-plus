#include "Window.h"
#include <iostream>

Window::Window(std::string name)
{
	window_ = SDL_CreateWindow(name.c_str(), 100, 100, 640, 480, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
	if (window_ == nullptr)
	{
		std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
		throw std::invalid_argument(static_cast<std::string>("SDL_CreateWindow Error: ") + SDL_GetError());
	}

	render_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (render_ == nullptr)
	{
		std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
		throw std::invalid_argument(static_cast<std::string>("SDL_CreateWindow Error: ") + SDL_GetError());
	}
}

Window::~Window()
{
	SDL_DestroyRenderer(render_);
	SDL_DestroyWindow(window_);
}

SDL_Renderer* Window::getRender() const
{
    return render_;
}

SDL_Window* Window::getWindow() const
{
	return window_;
}

math::Vector2D Window::getSize() const
{
	return math::Vector2D(width, height);
}
