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
	class Model : public IResources
	{
	private:
		std::vector<Vertex> vertexBFF;
		std::vector<uint32_t> indexBFF;

	public:
		void loadOBJ(const std::string& path);
		void unloadOBJ();


		std::vector<Vertex> getVertexBuffer() 
		{ 
			return vertexBFF;
		}

		std::vector<uint32_t> getIndexBuffer() 
		{ 
			return indexBFF;
		}


	};
}