#pragma once
#include <Collider.h>
#include <Platform.h>
class Actor
{
public:
	SphereCollider collider;
	Mesh* model;
	bool isGrounded;
	float velocity=0;
	float jumpHeight;
	Actor();
	void Update(std::vector<Platform*> platforms);
	void Jump(float height);
};