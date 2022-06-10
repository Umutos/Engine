#include <Actor.h>

Actor::Actor(SphereCollider collider, Mesh* model, float jumpHeight)
{
	this->collider = collider;
	this->model = model;
	this->jumpHeight = jumpHeight;
}

void Actor::Jump()
{
	velocity += sqrt(GRAVITY * jumpHeight * -2);
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


			Vector3D distancePlayerCollider = Vector3D(*collider.position - *platforms[i].collider.position);


			Vector3D pup = Vector3D(rotation.matrixTab4[1][0], rotation.matrixTab4[1][1], rotation.matrixTab4[1][2]);
			Vector3D prght = Vector3D(rotation.matrixTab4[0][0], rotation.matrixTab4[0][1], rotation.matrixTab4[0][2]);
			Vector3D pfwd = Vector3D(rotation.matrixTab4[2][0], rotation.matrixTab4[2][1], rotation.matrixTab4[2][2]);
			float playerRight = prght.Dot(distancePlayerCollider);
			float playerUp = pup.Dot(distancePlayerCollider);
			float playerFwd = pfwd.Dot(distancePlayerCollider);
			dotCenterUp = playerUp;
			dotCenterRight = playerRight;
			dotCenterFwd = playerFwd;
			if (playerUp > 0)
			{
				distancePlayerCollider = Vector3D(*collider.position - *platforms[i].collider.position + Vector3D(halfSizeRotated.matrixTab4[1][0], halfSizeRotated.matrixTab4[1][1], halfSizeRotated.matrixTab4[1][2]));

			}
			else if (playerUp < 0)
			{
				distancePlayerCollider = Vector3D(*collider.position - *platforms[i].collider.position - Vector3D(halfSizeRotated.matrixTab4[1][0], halfSizeRotated.matrixTab4[1][1], halfSizeRotated.matrixTab4[1][2]));
			}
			float playerUp2 = pup.Dot(distancePlayerCollider);

			if (playerRight > 0)
			{
				distancePlayerCollider = Vector3D(*collider.position - *platforms[i].collider.position - Vector3D(halfSizeRotated.matrixTab4[0][0], halfSizeRotated.matrixTab4[0][1], halfSizeRotated.matrixTab4[0][2]));
			}
			else if (playerRight < 0)
			{
				distancePlayerCollider = Vector3D(*collider.position - *platforms[i].collider.position + Vector3D(halfSizeRotated.matrixTab4[0][0], halfSizeRotated.matrixTab4[0][1], halfSizeRotated.matrixTab4[0][2]));
			}
			float playerRight2 = prght.Dot(distancePlayerCollider);

			if (playerFwd > 0)
			{
				distancePlayerCollider = Vector3D(*collider.position - *platforms[i].collider.position - Vector3D(halfSizeRotated.matrixTab4[2][0], halfSizeRotated.matrixTab4[2][1], halfSizeRotated.matrixTab4[2][2]));

			}
			else if (playerFwd < 0)
			{
				distancePlayerCollider = Vector3D(*collider.position - *platforms[i].collider.position + Vector3D(halfSizeRotated.matrixTab4[2][0], halfSizeRotated.matrixTab4[2][1], halfSizeRotated.matrixTab4[2][2]));
			}
			float playerFwd2 = pfwd.Dot(distancePlayerCollider);

			float fmodz = fmod(platforms[i].collider.obb.rotation->z, M_PI);
			float fmodx = fmod(platforms[i].collider.obb.rotation->x, M_PI);
			dotUp = playerUp2;
			dotRight = playerRight2;
			dotFwd = playerFwd2;

			if (playerUp2 > 0 && playerUp > 0)
			{
				isGrounded = true;
			}
			if (playerUp2 < 0 && playerUp < 0)
			{
				*collider.position = *collider.position - Vector3D(rotation.matrixTab4[1][0], rotation.matrixTab4[1][1], rotation.matrixTab4[1][2]);
			}
			if (playerRight2 > 0 && playerRight > 0)
			{
				*collider.position = *collider.position + Vector3D(rotation.matrixTab4[0][0], rotation.matrixTab4[0][1], rotation.matrixTab4[0][2]);
			}
			else if (playerRight2 < 0 && playerRight < 0)
			{
				*collider.position = *collider.position - Vector3D(rotation.matrixTab4[0][0], rotation.matrixTab4[0][1], rotation.matrixTab4[0][2]);
			}
			if (playerFwd2 > 0 && playerFwd > 0)
			{
				*collider.position = *collider.position + Vector3D(rotation.matrixTab4[2][0], rotation.matrixTab4[2][1], rotation.matrixTab4[2][2]);
			}
			else if (playerFwd2 < 0 && playerFwd < 0)
			{
				*collider.position = *collider.position - Vector3D(rotation.matrixTab4[2][0], rotation.matrixTab4[2][1], rotation.matrixTab4[2][2]);
			}
			

			





			if (((fmodz < -0.3 || fmodz > 0.3) && (fmodz < 3.11 || fmodz > 3.17)) || ((fmodx < -0.3 || fmodx > 0.3) && (fmodx < 3.11 || fmodx > 3.17)))
				*collider.position = *collider.position + (Vector3D(rotation.matrixTab4[1][0], rotation.matrixTab4[1][1], rotation.matrixTab4[1][2])) * 0.1;

		}
	}

	velocity += GRAVITY * deltaTime;
	if (isGrounded && velocity < 0)
		velocity = 0;


	collider.position->y = collider.position->y + velocity;
}