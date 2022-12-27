#include "TextComp.h"

#include <iostream>
#include <SDL_ttf.h>
#include <stdexcept>


void ui::TextComp::onMount()
{
	fontSize(100);
	text("None");
}

void ui::TextComp::onRender(SDL_Renderer* renderer)
{
	SDL_RenderCopyF(renderer, texture_, nullptr, absoluteRect().toSdl());
}

void ui::TextComp::onDestroy()
{
	if (font_ != nullptr)
	{
		TTF_CloseFont(font_);
		SDL_DestroyTexture(texture_);
	}
}

void ui::TextComp::onVisible()
{
	isEnable(true);
}

void ui::TextComp::onInvisible()
{
	isEnable(false);
}

int ui::TextComp::clip() const
{
	return clip_;
}

void ui::TextComp::clip(const int width)
{
	clip_ = width;
}

int ui::TextComp::fontSize() const
{
	return fz_;
}

void ui::TextComp::fontSize(const int fz)
{
	if (font_ != nullptr)
		TTF_CloseFont(font_);

	font_ = TTF_OpenFont("./res/Inter/Inter.ttf", fz);
	fz_ = fz;
}

void ui::TextComp::text(std::string* ftext)
{
	if (texture_ != nullptr)
		SDL_DestroyTexture(texture_);

	text_ = ftext;
	constexpr SDL_Color color{ 255, 255, 255, 255 };

	SDL_Surface* surf = TTF_RenderText_Blended(font_, text_->c_str(), color);
	if (clip_ > 0)
	{
		SDL_Rect clip{ 0, 0, clip_, fontSize()};
		auto sur = SDL_CreateRGBSurface(SDL_SWSURFACE, clip_, fontSize(), 32, 0, 0, 0, 0);
		SDL_SetSurfaceBlendMode(sur, SDL_BLENDMODE_ADD);
		SDL_BlitSurface(surf, &clip, sur, nullptr);

		texture_ = SDL_CreateTextureFromSurface(window_->getRender(), sur);
		SDL_FreeSurface(sur);
	}
	else
	{
		texture_ = SDL_CreateTextureFromSurface(window_->getRender(), surf);
	}
	
	int w;
	int h;
	SDL_QueryTexture(texture_, nullptr, nullptr, &w, &h);
	SDL_FreeSurface(surf);

	size(w, h);
}

void ui::TextComp::text(std::string ftext)
{
	text(&ftext);
}
