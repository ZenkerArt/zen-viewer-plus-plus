#pragma once
#include <SDL.h>
#include <string>

#include "DropManager.h"
#include "math/Vector2D.h"

class Window
{
	SDL_Renderer* render_;
	SDL_Window* window_;
	//const std::string* name_;
public:
	int width = 1;
	int height = 1;
	DropManager* dropManager = nullptr;

	explicit Window(std::string name);
	~Window();

	SDL_Renderer* getRender() const;
	SDL_Window* getWindow() const;
	math::Vector2D getSize() const;
};

