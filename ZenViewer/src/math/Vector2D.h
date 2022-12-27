#pragma once
namespace math
{
	struct Vector2D
	{
		//~Vector2D() = delete;

		float x = 0;
		float y = 0;

		Vector2D operator+(Vector2D other) const;
		Vector2D operator+(float other) const;

		Vector2D operator-(Vector2D other) const;
		Vector2D operator-(float other) const;

		Vector2D operator*(Vector2D other) const;
		Vector2D operator*(float other) const;

		Vector2D operator/(Vector2D other) const;
		Vector2D operator/(float other) const;

		Vector2D* operator=(Vector2D other);

		Vector2D* operator+=(Vector2D other);
		Vector2D* operator+=(float other);

		Vector2D* operator-=(Vector2D other);
		Vector2D* operator-=(float other);

		Vector2D* operator*=(Vector2D other);
		Vector2D* operator*=(float other);

		Vector2D* operator/=(Vector2D other);
		Vector2D* operator/=(float other);

		bool operator==(Vector2D other) const;
		bool operator!=(Vector2D other) const;


		float operator[](int other) const;


		[[nodiscard]] float length() const;

		Vector2D round();

		static Vector2D fill(float value);
		[[nodiscard]] Vector2D invert() const;

	};
}