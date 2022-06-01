#pragma once

#include <iostream>
#include <vector>
#include <Maths.h>
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <Model.h>
#include <Shader.h>

using namespace Resources;

namespace LowRenderer
{

	class Mesh
	{
	private:
		Model* modelOriginal;

	public:

		
		Matrix4 mat4;
		Matrix4 *par;
		Vector3D pos;
		Vector3D rot;
		Vector3D scl;

		GLuint texture;
		static std::vector<GLuint> texture1;

		void Update(unsigned int shaderProgram, Matrix4 PVMatrix);
		Mesh(Model* model, Vector3D Rotation, Vector3D Position, Vector3D Scale, const char* fileName);
		Mesh() {}

		Matrix4 ModelMatrixPop()
		{
			return mat4.CreateTransformMatrix(rot, pos, scl);
		}

	};
}

