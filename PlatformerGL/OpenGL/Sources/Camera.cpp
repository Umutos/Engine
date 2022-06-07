#include <Camera.h>

using namespace LowRenderer;

void Camera::CameraWithMouse(GLFWwindow* window, float x, float y)
{
	if (firstMouse)
	{
		moveX = x;
		moveY = y;
		firstMouse = false;
	}
	
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
	Vector3D direction;
	direction = Vector3D(cos(Radian(angle)) * cos(Radian(pitch)), sin(Radian(pitch)), sin(Radian(angle)) * cos(Radian(pitch)));

	direction.Normalize();
	camFront = direction;
}