#pragma once
#include "stdafx.h"
#include "Triangle.h"

struct Mesh 
{
public:
	Mesh(): Triangles(NULL), Length(0) {}
	Mesh(Triangle _triangles[], int _length):Triangles(_triangles),Length(_length){}

public:
	Triangle* Triangles;
	int Length;

};