#pragma once
#include <Collider.h>


class Platform
{
public:
	OBBCollider collider;
	Mesh* model;
	Platform(OBBCollider collider, Mesh* model);
};