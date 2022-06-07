#pragma once
#include <Collider.h>
#define GRAVITY       -10

class Platform
{
public:
	OBBCollider collider;
	Mesh* model;


};