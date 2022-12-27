#pragma once
#include <filesystem>
#include <string>
#include <SDL.h>
#include "./math/Vector2D.h"

class Image
{
public:
	Image() = default;
	~Image();

	Image* setPath(const std::filesystem::directory_entry& path);
	Image* loadOriginal();
	Image* loadResolution();
	Image* loadResolutionFromPath(const std::wstring& path);
	Image* loadTexture(SDL_Renderer* render);
	math::Vector2D getNatureSize();

	void setSurface(SDL_Surface* img);

	void draw(SDL_Renderer* render, math::Vector2D pos, math::Vector2D size) const;
	void destroy();

	unsigned int id = 0;
protected:
	SDL_Texture* image_ = nullptr;
	SDL_Surface* surface_ = nullptr;
	std::filesystem::directory_entry originalPath_;
	math::Vector2D natureSize_{};

	bool isLoaded_ = false;
};

