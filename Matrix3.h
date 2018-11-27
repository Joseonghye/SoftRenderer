#pragma once

struct Matrix3
{
public:
	float _11, _12, _13;
	float _21, _22, _23;
	float _31, _32, _33;

	Matrix3() : _11(0), _12(0), _13(0), _21(0), _22(0), _23(0), _31(0), _32(0), _33(0) {}

	void SetIdentity()
	{
		_11 = 1.0f;
		_12 = 0;
		_13 = 0;
		_21 = 0;
		_22 = 1;
		_23 = 0;
		_31 = 0;
		_32 = 0;
		_33 = 1;
	}

	void SetScale(float intX, float intY,float intZ)
	{
		SetIdentity();
		_11 = intX;
		_22 = intY;
		_33 = intZ;
	}

	void SetRotation(float degree)
	{
		SetIdentity();
		float radian = Deg2Rad(degree);
		_11 = cosf(radian);
		_12 = -sinf(radian);
		_21 = -_12;
		_22 = _11;
	}

	void SetTranslation(float InX, float InY)
	{
		SetIdentity();
		_13 = InX;
		_23 = InY;
	}

	void Transpose()
	{
		float temp = _12;
		_12 = _21;
		_21 = temp;
		temp = _13;
		_13 = _31;
		_31 = temp;
	}

	Matrix3 operator*(const Matrix3& Mat) const;
};