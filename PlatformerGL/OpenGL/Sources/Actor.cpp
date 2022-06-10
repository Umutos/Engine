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

			Vector3D prght = Vector3D(rotation.matrixTab4[0][0], rotation.matrixTab4[0][1], rotation.matrixTab4[0][2]);
			prght.Normalize();
			Vector3D prght2 = Vector3D(*collider.position - *platforms[i].collider.position);
			prght2.Normalize();

			float playerRight = Vector3D(rotation.matrixTab4[0][0], rotation.matrixTab4[0][1], rotation.matrixTab4[0][2]).Dot(Vector3D(*collider.position - *platforms[i].collider.position));
			
			Vector3D pup = Vector3D(rotation.matrixTab4[1][0], rotation.matrixTab4[1][1], rotation.matrixTab4[1][2]);
			pup.Normalize();
			Vector3D pup2 = Vector3D(*collider.position - *platforms[i].collider.position);
			pup2.Normalize();
			float playerUp = pup.Dot(pup2);

			
			float playerUp = prght.Dot(prght2);
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
			float fmodz = fmod(platforms[i].collider.obb.rotation->z, M_PI);
			float fmodx = fmod(platforms[i].collider.obb.rotation->x, M_PI);
			if(((fmodz<-0.3|| fmodz > 0.3) && (fmodz < 3.11 || fmodz > 3.17))||((fmodx < -0.3 || fmodx > 0.3) && (fmodx < 3.11 || fmodx > 3.17)))
			*collider.position = *collider.position + (Vector3D(rotation.matrixTab4[1][0], rotation.matrixTab4[1][1], rotation.matrixTab4[1][2])) * 0.1;

		}
	}

	velocity += GRAVITY * deltaTime;
	if (isGrounded && velocity < 0)
		velocity = 0;


	collider.position->y = collider.position->y + velocity;
}