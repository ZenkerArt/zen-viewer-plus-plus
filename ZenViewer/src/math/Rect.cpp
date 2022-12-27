#include "Rect.h"

namespace math
{
	Rect Rect::operator*(const Vector2D vector) const
	{
		return Rect{
			x * vector.x,
			y * vector.y,
			w * vector.x,
			h * vector.y
		};
	}

	Rect Rect::operator/(const Vector2D vector) const
	{
		return Rect{
			x / vector.x,
			y / vector.y,
			w / vector.x,
			h / vector.y
		};
	}

	Rect Rect::operator+(const Rect rect) const
	{
		return Rect{
			x + rect.x,
			y + rect.y,
			w + rect.w,
			h + rect.h
		};
	}

	SDL_FRect* Rect::toSdl() const
	{
		return new SDL_FRect{ x, y, w, h };
	}
}
