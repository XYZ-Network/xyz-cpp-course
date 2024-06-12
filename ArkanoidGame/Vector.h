#pragma once

namespace ArkanoidGame
{
	template<typename T>
	struct Vector2D
	{
		T x = (T)0;
		T y = (T)0;
	};

	using Vector2Df = Vector2D<float>;
	using Vector2Di = Vector2D<int>;
	using Position = Vector2Df;

	template<typename T>
	Vector2D<T> operator+(const Vector2D<T>& lhs, const Vector2D<T>& rhs)
	{
		return { lhs.x + rhs.x, lhs.y + rhs.y };
	}

	template<typename T>
	Vector2D<T> operator-(const Vector2D<T>& lhs, const Vector2D<T>& rhs)
	{
		return { lhs.x - rhs.x, lhs.y - rhs.y };
	}

	template<typename T>
	bool operator==(const Vector2D<T>& lhs, const Vector2D<T>& rhs)
	{
		return lhs.x == rhs.x && lhs.y == rhs.y;
	}

	template<typename T>
	float GetVectorLength(const Vector2D<T>& vector)
	{
		return sqrtf(vector.x * vector.x + vector.y * vector.y);
	}

	// This complex template allows us to convert any vector type to any other vector type (like our Vector2D to SFML's Vector and vice versa)
	template<typename U, typename V>
	U Convert(const V& v)
	{
		// decltype deduces type from expression
		return { static_cast<decltype(U::x)>(v.x), static_cast<decltype(U::y)>(v.y) };
	}
}
