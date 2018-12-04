#pragma once
#include "Vector.h"
#include "stdafx.h"

struct Transform2D
{
public:
	Transform2D():Angle(0) { SetTRSMatrix(); }
	Transform2D(Vector2 InPosition, float InAngle, Vector2 InScale) 
		: Position(InPosition), Angle(InAngle), Scale(InScale) {
		SetTRSMatrix();
	}

	void SetCamera(Vector2 InPosition, float InAngle)
	{
		Position = InPosition;
		Angle = InAngle;

		SetViewMatrix();
	}

private:
	void SetTRSMatrix()
	{
		Matrix3 tMat, rMat, sMat;
		sMat.SetScale(Scale.X, Scale.Y, 1);
		rMat.SetRotation(Angle);
		tMat.SetTranslation(Position.X, Position.Y);
		TRS = tMat * rMat * sMat;
	}

	void SetViewMatrix()
	{
		Matrix3 itMat, irMat;
		irMat.SetRotation(Angle);
		irMat.Transpose();

		itMat.SetInverseTranslation(Position.X, Position.Y);

		ViewMatrix = irMat * itMat;
	}

public:
	Vector2 Position;
	float Angle;
	Vector2 Scale;
	Matrix3 TRS;
	Matrix3 ViewMatrix;
};