#include <Camera.h>

using namespace LowRenderer;

Matrix4 Camera::LookAt(Vector3D eye, Vector3D target, Vector3D up)
{
	Vector3D zaxis = target - eye;
	target.Normalize();
	Vector3D xaxis = zaxis.CrossProduct(up);
	xaxis.Normalize();
	Vector3D yaxis = xaxis.CrossProduct(zaxis);

	zaxis * -1;

	float viewMatrix[4][4] = {
		{xaxis.x, xaxis.y, xaxis.z, -xaxis.Dot(eye)},
		{yaxis.x, yaxis.y, yaxis.z, -yaxis.Dot(eye)},
		{zaxis.x, zaxis.y, zaxis.z, -zaxis.Dot(eye)},
		{0, 0, 0, 1}
	};

	return viewMatrix;
}

void Camera::Update(Vector3D target)
{
	Matrix4 mat4;
	viewMatrix = LookAt(camPos, target, camUP);

}

void Camera::CameraWithMouse(GLFWwindow* window, float x, float y)
{
	if (firstMouse)
	{
		moveX = x;
		moveY = y;
		firstMouse = false;
	}

	Vector3D direction;
	
	if (mouseMove)
	{
		float offsetX = moveX - x;
		float offsetY = y - moveY;
		moveX = x;
		moveY = y;

		float sensitivity = 0.1f;
		offsetX *= sensitivity;
		offsetY *= sensitivity;

		angle += offsetX;
		pitch += offsetY;

		if (pitch > 89)
			pitch = 89;
		if (pitch < -89)
			pitch = -89;
	}

	direction = Vector3D(cos(Radian(angle)) * cos(Radian(pitch)), sin(Radian(pitch)), sin(Radian(angle)) * cos(Radian(pitch)));
	direction.Normalize();
	
	camFront = direction;
	
}