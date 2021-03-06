#pragma once

struct Matrix2
{
public:
	float _11, _12;
	float _21, _22;

	Matrix2() : _11(1), _12(1), _21(1), _22(1) {}
	Matrix2(float In11, float In12, float In21, float In22) :_11(In11), _12(In12), _21(In21), _22(In22) {}

public:
	void SetIdentity()
	{
		_11 = 1.0f;
		_12 = 0.0f;
		_21 = 0.0f;
		_22 = 1.0f;
	}

	void SetScale(float IntX, float IntY)
	{
		SetIdentity();
		_11 = IntX;
		_22 = IntY;
	}

	void SetRotation(float degree)
	{
		float radian = Deg2Rad(degree);
		_11 = cosf(radian);
		_12 = -sinf(radian);
		_21 = sinf(radian);
		_22 = cosf(radian);
	}

	//����� 
	void Transpose()
	{
		float __12 = _12;
		_12 = _21;
		_21 = __12;
	}

	Matrix2 operator* (const Matrix2& Mat) const;
};