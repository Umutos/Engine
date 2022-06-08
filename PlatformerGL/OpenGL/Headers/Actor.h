#pragma once
#include <Collider.h>
#include <Platform.h>
#define GRAVITY     -0.5

class Actor
{

public:
	SphereCollider collider;
	Mesh* model;
	float deltaTime;
	float lastFrame;
	bool isGrounded;
	float velocity=0;
	float jumpHeight;
	Actor(SphereCollider collider, Mesh* model, float jumpHeight);
	Actor() {};
	void Update(std::vector<Platform> platforms);
	void Jump();
};