#pragma once
#include <SDL.h>
#include <zlib.h>

SDL_Surface* imageThumbnail(SDL_Surface* img, const float limit);
SDL_Surface* imageResize(SDL_Surface* img, int w, int h);
SDL_Surface* imageDecompress(const Byte* compressImage, uLong* uncompressedSize, uLong* compressedSize);
char* imageCompress(SDL_Surface* img, uLong* uncompressedSize, uLong* compressedSize);

void imageBlur(const SDL_Surface* img, int blurExtent = 1);
