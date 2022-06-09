#include <Actor.h>

Actor::Actor(SphereCollider collider, Mesh* model, float jumpHeight)
{
	this->collider = collider;
	this->model = model;
	this->jumpHeight = jumpHeight;
}

void Actor::Jump()
{
	velocity += sqrtf(GRAVITY * jumpHeight * -2);
}

void Actor::Update(std::vector<Platform> platforms)
{

	collider.Update();
	float currentFrame = glfwGetTime();
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;

	isGrounded = false;

	for (int i = 0; i < platforms.size(); i++)
	{
		if (SphereOBBCol(collider, platforms[i].collider))
		{

			Matrix4 rotation = platforms[i].collider.obb.umv();
			Matrix4 halfSizeRotated;
			for (int j = 0; j < 3; j++)
			{
				halfSizeRotated.Matrix4V[j] = platforms[i].collider.obb.halfSize().xyz[j] * Vector3D(rotation.matrixTab4[j][0], rotation.matrixTab4[j][1], rotation.matrixTab4[j][2]);
			}
			float playerRight = Vector3D(rotation.matrixTab4[0][0], rotation.matrixTab4[0][1], rotation.matrixTab4[0][2]).Dot(Vector3D(*collider.position - *platforms[i].collider.position));
			
			Vector3D pup = Vector3D(rotation.matrixTab4[1][0], rotation.matrixTab4[1][1], rotation.matrixTab4[1][2]);
			pup.Normalize();
			Vector3D pup2 = Vector3D(*collider.position - *platforms[i].collider.position);
			pup2.Normalize();
			float playerUp = pup.Dot(pup2);
			float playerFwd = Vector3D(rotation.matrixTab4[2][0], rotation.matrixTab4[2][1], rotation.matrixTab4[2][2]).Dot(Vector3D(*collider.position - *platforms[i].collider.position));
			dot = playerUp;
			if (playerUp >= 0)
			{
				isGrounded = true;
			}
			else
			{
				collider.position->y++;
			}
			*collider.position = *collider.position + (Vector3D(rotation.matrixTab4[1][0], rotation.matrixTab4[1][1], rotation.matrixTab4[1][2])) * 0.1;

		}
	}

	velocity += GRAVITY * deltaTime;
	if (isGrounded && velocity < 0)
		velocity = 0;


	collider.position->y = collider.position->y + velocity;
}