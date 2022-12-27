#pragma once
#include "Vector2D.h"
#include "SDL.h"

namespace math
{
	struct Rect
	{
		float x = 0;
		float y = 0;
		float w = 0;
		float h = 0;

		Rect operator * (Vector2D vector) const;
		Rect operator / (Vector2D vector) const;
		Rect operator + (Rect rect) const;

		[[nodiscard]] SDL_FRect* toSdl() const;
	};

}

