#pragma once
#include "stdafx.h"
#include "Matrix.h"

struct Vector2
{
public:
	float X;
	float Y;

public:
	Vector2() : X(0), Y(0) {}
	Vector2(float intX, float intY) : X(intX), Y(intY) {}
	
	static float Dist(const Vector2& V1, const Vector2& V2);
	static float DistSquard(const Vector2& V1, const Vector2& V2);

	Vector2 operator* (const Matrix2& Mat) const;
	Vector2 operator* (float Scale) const;
	Vector2 operator+ (const Vector2& V) const;

	bool Equals(const Vector2& V, float colorance = KINDA_SMALL_NUMBER) const;
};
