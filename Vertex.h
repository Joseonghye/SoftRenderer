#pragma once

#include "stdafx.h"
#include "Vector.h"

struct Vertex 
{
public:
	Vertex() : color(RGB32(0, 0, 0)) {}
	Vertex(Vector3 v) :position(v), color(RGB32(0, 0, 0)) {}
	Vertex(Vector3 v, ULONG c) :position(v),color(c){}
	Vertex(Vector3 v, ULONG c,Vector2& InUV) :position(v), color(c),uv(InUV) {}

	Vector3 position;
	Vector2 uv;
	ULONG color;
};
