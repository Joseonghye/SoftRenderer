#pragma once
#include "Transform.h"
#include "stdafx.h"
#include "Mesh.h"

struct GameObject2D
{
	GameObject2D() {}
	GameObject2D(Transform2D InTransform, Mesh InMesh) : 
		Transform(InTransform),Mesh(InMesh) {}

public:
	Transform2D Transform;
	Mesh Mesh;

};
