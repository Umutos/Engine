#pragma once
#include <Maths.h>
#include <GLFW/glfw3.h>

namespace LowRenderer
{
	class Camera
	{
	public:
		Vector3D camPos = { 0.f, 10.f, 30.f };
		Vector3D camUP = { 0.f, 1.f, 0.f };
		Vector3D camRight = { 0.f, 0.f, 0.f };
		Vector3D camFront = { camPos.x + cos(Radian(angle)) * cos(Radian(pitch)), camPos.y + sin(Radian(pitch)), camPos.z + sin(Radian(angle)) * cos(Radian(pitch)) };

		Matrix4 modelMatrix;
		Matrix4 viewMatrix;
		Matrix4 projectionMatrix;

		bool firstMouse = true;
		bool mouseMove = false;
		float moveX = 800.0f / 2.0;
		float moveY = 600.0 / 2.0;

		float angle = 90;
		float pitch = 0;
		float moveSpeed = 0.05f;
		float jumpSpeed = 10.0f;


	public:

		void CameraWithMouse(GLFWwindow* window, float xpos, float ypos);

	};
}
