#include "Math.h"
#include <iostream>

namespace math
{
	float aLerp(const float start, const float end, const float time)
	{
		if (isnan(start) || isnan(end)) {
			return 0;
		}

		if (abs(start - end) < .5f) {
			return end;
		}

		return (start * (1 - time) + end * time);
	}

	Vector2D aLerp(const Vector2D start, const Vector2D end, const float time) {

		return Vector2D{
			aLerp(start.x, end.x, time),
			aLerp(start.y, end.y, time)
		};
	}

	void printVector2D(const Vector2D vec)
	{
		std::cout << "X: " << vec.x << ", Y:" << vec.y << std::endl;
	}
}