#pragma once
#include "Vector2D.h"

namespace math
{
	float aLerp(float start, float end, float time);
	math::Vector2D aLerp(Vector2D start, Vector2D end, float time);
	void printVector2D(Vector2D vec);
}
