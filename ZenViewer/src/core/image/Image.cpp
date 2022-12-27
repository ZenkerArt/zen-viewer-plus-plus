#include "Image.h"
#include <SDL_image.h>
#include "Utils.h"
#include <exiv2/exiv2.hpp>
#include <filesystem>

Image::~Image()
{
	destroy();
}

Image* Image::setPath(const std::filesystem::directory_entry& path)
{
	originalPath_ = path;
	return this;
}

Image* Image::loadOriginal()
{
	_cputws(originalPath_.path().wstring().data());
	setSurface(IMG_Load(makeUtf8Str(originalPath_.path().u8string()).c_str()));
	return this;
}

Image* Image::loadResolution()
{
	loadResolutionFromPath(originalPath_.path().wstring());
	return this;
}

Image* Image::loadTexture(SDL_Renderer* render)
{
	if (this->surface_ != nullptr && !this->isLoaded_ && image_ == nullptr) {
		image_ = SDL_CreateTextureFromSurface(render, surface_);
		if (image_ == nullptr) {
			runtimeError("IMG_LoadTexture Error: " + std::string(SDL_GetError()));
		}

		int bW, bH;
		SDL_QueryTexture(image_, nullptr, nullptr, &bW, &bH);
		isLoaded_ = true;

	}
	return this;
}

void Image::setSurface(SDL_Surface* img)
{
	surface_ = img;
}

Image* Image::loadResolutionFromPath(const std::wstring& path)
{
	if (path.empty())
	{
		std::cout << "Path empty" << std::endl;
		return this;
	}
	const auto image = Exiv2::ImageFactory::open(originalPath_.path().generic_wstring());
	image->readMetadata();
	std::cout << "Loading Resolution: " << image->pixelWidth() << " x " << image->pixelHeight() << std::endl << std::endl;

	natureSize_.x = static_cast<float>(image->pixelWidth());
	natureSize_.y = static_cast<float>(image->pixelHeight());
	isLoaded_ = false;

	return this;
}

void Image::destroy()
{
	if (isLoaded_) {
		std::cout << "Destroy image: " << image_ << std::endl;
		SDL_DestroyTexture(image_);
		image_ = nullptr;
		isLoaded_ = false;

		SDL_FreeSurface(surface_);
		surface_ = nullptr;
		isLoaded_ = false;
	}
}

math::Vector2D Image::getNatureSize()
{
	return natureSize_;
}

void Image::draw(SDL_Renderer* render, const math::Vector2D pos, const math::Vector2D size) const
{
	const auto rect = SDL_FRect{
		pos.x,
		pos.y,
		size.x,
		size.y,
	};
	if (image_ != nullptr)
		SDL_RenderCopyF(render, image_, nullptr, &rect);
}

