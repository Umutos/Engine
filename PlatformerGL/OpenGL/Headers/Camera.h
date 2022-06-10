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
		Vector3D camRight = { 1.f, 0.f, 0.f };
		Vector3D camFront = { 0.f, 0.f, 1.f };

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
		float rotationSpeed = 0.5f;
		float jumpSpeed = 10.0f;


	public:
		Camera()
		{
			Matrix4 mat4;
			projectionMatrix = mat4.GetProjection(80.f, 0.005f, 1000.f);
		}

	public:

		Matrix4 LookAt(Vector3D eye, Vector3D target, Vector3D up);
		void CameraWithMouse(GLFWwindow* window, float xpos, float ypos);
		void Update(Vector3D target);

	};
}
