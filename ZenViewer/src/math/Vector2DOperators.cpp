#include "Vector2D.h"

namespace math
{
	Vector2D Vector2D::operator+(const Vector2D other) const
	{
		return Vector2D{
			x + other.x,
			y + other.y
		};
	}

	Vector2D Vector2D::operator+(const float other) const
	{
		return Vector2D{
			x + other,
			y + other
		};
	}
	Vector2D Vector2D::operator-(const Vector2D other) const
	{
		return Vector2D{
			x - other.x,
			y - other.y
		};
	}

	Vector2D Vector2D::operator-(const float other) const
	{
		return Vector2D{
			x - other,
			y - other
		};
	}
	Vector2D Vector2D::operator*(const Vector2D other) const
	{
		return Vector2D{
			x * other.x,
			y * other.y
		};
	}

	Vector2D Vector2D::operator*(const float other) const
	{
		return Vector2D{
			x * other,
			y * other
		};
	}
	Vector2D Vector2D::operator/(const Vector2D other) const
	{
		return Vector2D{
			x / other.x,
			y / other.y
		};
	}

	Vector2D Vector2D::operator/(const float other) const
	{
		return Vector2D{
			x / other,
			y / other
		};
	}

	Vector2D* Vector2D::operator=(const Vector2D other)
	{
		this->x = other.x;
		this->y = other.y;
		return this;
	}

	Vector2D* Vector2D::operator+=(const Vector2D other)
	{
		this->x += other.x;
		this->y += other.y;
		return this;
	}

	Vector2D* Vector2D::operator+=(const float other)
	{
		this->x += other;
		this->y += other;
		return this;
	}

	Vector2D* Vector2D::operator-=(const Vector2D other)
	{
		this->x -= other.x;
		this->y -= other.y;
		return this;
	}

	Vector2D* Vector2D::operator-=(const float other)
	{
		this->x -= other;
		this->y -= other;
		return this;
	}

	Vector2D* Vector2D::operator*=(const Vector2D other)
	{
		this->x *= other.x;
		this->y *= other.y;
		return this;
	}

	Vector2D* Vector2D::operator*=(const float other)
	{
		this->x *= other;
		this->y *= other;
		return this;
	}

	Vector2D* Vector2D::operator/=(const Vector2D other)
	{
		this->x /= other.x;
		this->y /= other.y;
		return this;
	}

	Vector2D* Vector2D::operator/=(const float other)
	{
		this->x /= other;
		this->y /= other;
		return this;
	}

	bool Vector2D::operator==(const Vector2D other) const
	{
		const int l1 = static_cast<int>(length());
		const int l2 = static_cast<int>(other.length());

		return l1 == l2;
	}

	bool Vector2D::operator!=(const Vector2D other) const
	{
		return !(*this == other);
	}

	float Vector2D::operator[](const int other) const
	{
		return (other == 0) ? x : y;
	}
}
