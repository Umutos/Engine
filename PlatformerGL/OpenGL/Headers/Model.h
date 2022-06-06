#pragma once
#include <vector>
#include <Maths.h>
#include <string>
#include <sstream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <fstream>
#include <filesystem>
#include <Assertion.h>
#include <IResources.h>

using namespace Core;
using namespace Core::Debug;

namespace Resources
{
	struct Vertex
	{
		Vector3D Position;
		Vector2D TextureUV;
		Vector3D Normal;
	};


	class Buffer {
	private:
	public:
		unsigned int buffer;
		Buffer(const void* data, unsigned int size);
		Buffer();
		~Buffer();
		void bind();
		void unbind();
	};


	class VertexAttributes
	{
	public:
		unsigned int vao;
		VertexAttributes();
		~VertexAttributes();
		void Load(std::vector<Vertex> vertices, std::vector<uint32_t> indexes, Buffer vbo, Buffer ebo);
		void bind();
		void unbind();

	};

	class Model : public IResources
	{
	public:
		std::vector<Vertex> vertexBFF;
		std::vector<uint32_t> indexBFF;
		VertexAttributes VAO;
		Buffer EBO;
		Buffer VBO;

	public:
		void loadOBJ(const std::string& path) override;
		void unloadOBJ();


	};
}