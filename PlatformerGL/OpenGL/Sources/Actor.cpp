#include <Actor.h>


void Actor::Jump(float height)
{
		velocity += sqrtf(GRAVITY*jumpHeight * -2 );
}

void Actor::Update(std::vector<Platform*> platforms)
{
	isGrounded = false;

	for (int i = 0; i < platforms.size(); i++)
	{
		if (SphereOBBCol(collider, platforms[i]->collider))
		{
			isGrounded = true;
		}
	}

	if (isGrounded && velocity < 0)
		velocity = 0;
}