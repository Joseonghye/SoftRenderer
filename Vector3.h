#pragma once
#include "Matrix.h"

struct Vector3 {
public:
	float X;
	float Y;
	float Z;

	Vector3() : X(0),Y(0),Z(0){}
	Vector3(float intX, float intY) : X(intX), Y(intY), Z(1) {}
	Vector3(float intX,float intY, float intZ) : X(intX),Y(intY),Z(intZ){}

	static float Dist(const Vector3& V1, const Vector3& V2);
	static float DistSquared(const Vector3& V1, const Vector3& V2);

	Vector3 operator* (const Matrix3& Mat) const;

	bool Equals(const Vector3& V, float tolorance = KINDA_SMALL_NUMBER) const;
};
