#pragma once
#include "stdafx.h"
#include "Triangle.h"

struct Mesh 
{
public:
	Mesh() {}
	Mesh(Triangle t1, Triangle t2) {
		Triangles[0] = t1;
		Triangles[1] = t2;
	}

public:
	Triangle Triangles[2];

};