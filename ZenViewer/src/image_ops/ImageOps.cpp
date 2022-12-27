#include "ImageOps.h"

#include <iostream>
#include <SDL_image.h>


SDL_Surface* imageResize(SDL_Surface* img, const int w, const int h)
{
	const int width = img->w;
	const int height = img->h;

	SDL_Rect sourceDimensions;
	sourceDimensions.x = 0;
	sourceDimensions.y = 0;
	sourceDimensions.w = width;
	sourceDimensions.h = height;

	SDL_Rect targetDimensions;
	targetDimensions.x = 0;
	targetDimensions.y = 0;
	targetDimensions.w = w;
	targetDimensions.h = h;

	SDL_Surface* p32BPPSurface = SDL_CreateRGBSurface(
		img->flags,
		sourceDimensions.w,
		sourceDimensions.h,
		32,
		img->format->Rmask,
		img->format->Gmask,
		img->format->Bmask,
		img->format->Amask);

	SDL_Surface* pScaleSurface = SDL_CreateRGBSurface(
		p32BPPSurface->flags,
		targetDimensions.w,
		targetDimensions.h,
		p32BPPSurface->format->BitsPerPixel,
		p32BPPSurface->format->Rmask,
		p32BPPSurface->format->Gmask,
		p32BPPSurface->format->Bmask,
		p32BPPSurface->format->Amask);


	if (pScaleSurface == nullptr || p32BPPSurface == nullptr) {
		std::cout << "ResizeImage Error: " << SDL_GetError() << std::endl;
		throw std::runtime_error(static_cast<std::string>("ResizeImage Error: ") + SDL_GetError());
	}

	if (SDL_BlitSurface(img, nullptr, p32BPPSurface, nullptr) < 0) {
		std::cout << "ResizeImage Error: " << SDL_GetError() << std::endl;
		throw std::runtime_error(static_cast<std::string>("ResizeImage Error: ") + SDL_GetError());
	}

	if (SDL_FillRect(pScaleSurface, &targetDimensions, SDL_MapRGBA(pScaleSurface->format, 255, 0, 0, 255) < 0) < 0) {
		std::cout << "ResizeImage Error: " << SDL_GetError() << std::endl;
		throw std::runtime_error(static_cast<std::string>("ResizeImage Error: ") + SDL_GetError());
	}


	if (SDL_BlitScaled(p32BPPSurface, nullptr, pScaleSurface, nullptr) < 0) {
		std::cout << "ResizeImage Error: " << SDL_GetError() << std::endl;
		throw std::runtime_error(static_cast<std::string>("ResizeImage Error: ") + SDL_GetError());
	}

	SDL_FreeSurface(p32BPPSurface);

	return pScaleSurface;
}

SDL_Surface* imageThumbnail(SDL_Surface* img, const float limit) {
	const auto width = static_cast<float>(img->w);
	const auto height = static_cast<float>(img->h);

	float scale = limit / width;

	if (const float scaleH = limit / height; scaleH < scale) {
		scale = scaleH;
	}

	return imageResize(img, static_cast<int>(width * scale), static_cast<int>(height * scale));
}

SDL_Surface* imageDecompress(const Byte* compressImage, uLong* uncompressedSize, uLong* compressedSize)
{
	const auto bitmap = new char[*uncompressedSize];

	uncompress2(reinterpret_cast<Bytef*>(bitmap), uncompressedSize, compressImage, compressedSize);
	SDL_Surface* surface = IMG_Load_RW(SDL_RWFromMem(bitmap, *uncompressedSize), true);
	delete[] bitmap;
	return surface;
}

char* imageCompress(SDL_Surface* img, uLong* uncompressedSize, uLong* compressedSize) {
	const auto w = img->w;
	const auto h = img->h;

	*uncompressedSize = 54 + 8 * w * h;
	*compressedSize = compressBound(*uncompressedSize);

	const auto bitmap = new char[*uncompressedSize];
	SDL_RWops* rw = SDL_RWFromMem(bitmap, *uncompressedSize);
	auto ret = SDL_SaveBMP_RW(img, rw, true);
	std::cout << SDL_GetError() << std::endl;

	const auto compressImage = new char[*compressedSize];
	auto res = compress2(reinterpret_cast<Byte*>(compressImage), compressedSize, reinterpret_cast<const Bytef*>(bitmap), *uncompressedSize, 1);

	return compressImage;
}

// from here https://bacprogramming.wordpress.com/2018/01/10/box-blur-with-sdl2/
void imageBlur(const SDL_Surface* img, const int blurExtent)
{
	for (int y = 0; y < img->h; y++)
	{
		for (int x = 0; x < (img->pitch / 4); x++)
		{
			Uint32 color = static_cast<Uint32*>(img->pixels)[(y * (img->pitch / 4)) + x];
			Uint8 r = 0, g = 0, b = 0, a = 0;
			SDL_GetRGBA(color, img->format, &r, &g, &b, &a);

			Uint32 rb = 0, gb = 0, bb = 0, ab = 0;

			for (int yo = -blurExtent; yo <= blurExtent; yo++)
			{
				for (int xo = -blurExtent; xo <= blurExtent; xo++) {
					if (y + yo >= 0 && x + xo >= 0
						&& y + yo < img->h && x + xo < (img->pitch / 4)
						)
					{
						const Uint32 colOth = static_cast<Uint32*>(img->pixels)[((y + yo)
							* (img->pitch / 4)) + (x + xo)];

						Uint8 ro = 0, go = 0, bo = 0, ao = 0;
						SDL_GetRGBA(colOth, img->format, &ro, &go, &bo, &ao);

						rb += ro;
						gb += go;
						bb += bo;
						ab += ao;
					}
				}
			}

			r = static_cast<Uint8>(rb / (((blurExtent * 2) + 1) * ((blurExtent * 2) + 1)));
			g = static_cast<Uint8>(gb / (((blurExtent * 2) + 1) * ((blurExtent * 2) + 1)));
			b = static_cast<Uint8>(bb / (((blurExtent * 2) + 1) * ((blurExtent * 2) + 1)));
			a = static_cast<Uint8>(ab / (((blurExtent * 2) + 1) * ((blurExtent * 2) + 1)));

			color = (r) | (g << 8) | (b << 16) | (a << 24);           static_cast<Uint32*>(img->pixels)[(y * (img->pitch / 4)) + x] = color;
		}
	}
}