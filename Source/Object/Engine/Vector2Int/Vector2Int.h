
//整数型のVector2とその仕様を定義

#pragma once

struct Vector2Int
{
	int x;
	int y;

	Vector2Int() : x(0), y(0) {}
	Vector2Int(int _x, int _y) : x(_x), y(_y) {}

	Vector2Int operator+(const Vector2Int& other) const
	{
		return Vector2Int(x + other.x, y + other.y);
	}
	Vector2Int operator-(const Vector2Int& other) const
	{
		return Vector2Int(x - other.x, y - other.y);
	}
	Vector2Int& operator+=(const Vector2Int& other)
	{
		x += other.x;
		y += other.y;
		return *this;
	}

	bool operator==(const Vector2Int& other) const
	{
		return x == other.x && y == other.y;
	}

	bool operator!=(const Vector2Int& other) const
	{
		return !(*this == other);
	}
};