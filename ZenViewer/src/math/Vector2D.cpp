#include "Vector2D.h"

#include <corecrt_math.h>
namespace math
{
	float Vector2D::length() const
	{
		return sqrtf(powf(x, 2) + powf(y, 2));
	}

	Vector2D Vector2D::round()
	{
		return Vector2D{
			x = roundf(x),
			y = roundf(y)
		};
	}

	Vector2D Vector2D::fill(const float value)
	{
		return Vector2D{ value, value };
	}

	Vector2D Vector2D::invert() const
	{
		return Vector2D{ -x, -y };
	}

}