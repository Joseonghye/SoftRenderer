#include "stdafx.h"
#include "Vector2.h"

float Vector2::Dist(const Vector2 & V1, const Vector2 & V2)
{
	float xLength = (V2.X - V1.X);
	float yLength = (V2.Y - V1.Y);
	return xLength*xLength + yLength*yLength;
}

float Vector2::DistSquard(const Vector2 & V1, const Vector2 & V2)
{
	float xLength = (V2.X - V1.X);
	float yLength = (V2.Y - V1.Y);
	return sqrtf(xLength*xLength + yLength*yLength);
}

Vector2 Vector2::operator*(const Matrix2 & Mat) const
{
	Vector2 result;
	result.X = X*Mat._11 + Y*Mat._12;
	result.Y = X*Mat._21 + Y*Mat._22;
	return result;
}

Vector2 Vector2::operator*(float Scale) const
{
	return Vector2(X*Scale, Y*Scale);
}

Vector2 Vector2::operator+(const Vector2 & V) const
{
	return Vector2(X + V.X, Y + V.Y);
}

bool Vector2::Equals(const Vector2 & V, float tolorance) const //오류 방지용 const
{
	return (fabs(X - V.X) <= tolorance) && (fabs(Y - V.Y) <= tolorance);
}
