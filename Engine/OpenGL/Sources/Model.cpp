#include <Model.h>
#include <iostream>

namespace Resources
{

	void VertexAttributes::Load(std::vector<Vertex> vertices, std::vector<uint32_t> indexes, Buffer vbo, Buffer ebo)
	{
		glGenBuffers(1, &vbo.buffer);
		glGenBuffers(1, &ebo.buffer);

		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);

		glBindBuffer(GL_ARRAY_BUFFER, vbo.buffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices.size(), vertices.data(), GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo.buffer);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint32_t) * indexes.size(), indexes.data(), GL_STATIC_DRAW);
		
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(5 * sizeof(float)));
		glEnableVertexAttribArray(2);

		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);


	}

	VertexAttributes::VertexAttributes() {}

	VertexAttributes::~VertexAttributes()
	{
		glDeleteVertexArrays(1, &vao);
	}

	void VertexAttributes::bind()
	{
		glBindVertexArray(vao);
	}

	void VertexAttributes::unbind()
	{
		glBindVertexArray(0);
	}

	Buffer::Buffer(const void* data, unsigned int size)
	{
		glGenBuffers(1, &buffer);
		glBindBuffer(GL_ARRAY_BUFFER, buffer);
		glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
	}

	Buffer::Buffer() {}

	Buffer::~Buffer()
	{
		glDeleteBuffers(1, &buffer);
	}

	void Buffer::bind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, buffer);
	}

	void Buffer::unbind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void Model::unloadOBJ()
	{
		vertexBFF.clear();
		indexBFF.clear();
	}

	void Model::loadOBJ(const std::string& path)
	{
		//Find Line
		std::string line;
		std::string firstLetter;
		std::stringstream findFirstLettre;

		//Face vectors
		std::vector<uint32_t> vectexPositionIndicies;
		std::vector<uint32_t> vertexTextureUVIndicies;
		std::vector<uint32_t> vectexNormalIndicies;

		//Vertex array
		std::vector<Vector3D> tempVertices;
		std::vector<Vector2D> tempUV;
		std::vector<Vector3D> tempNormal;

		//Other
		GLint temp;
		std::ifstream file(path);

		//Debug for file
		ASSERT(file.is_open(), "Impossible to open the file !\n");

		while (getline(file, line))
		{
			findFirstLettre.clear();
			findFirstLettre.str(line);
			findFirstLettre >> firstLetter;

			if (firstLetter == "v")
			{
				Vector3D vertex;
				findFirstLettre >> vertex.x >> vertex.y >> vertex.z;
				tempVertices.push_back(vertex);
			}

			if (firstLetter == "vt")
			{
				Vector2D uv;
				findFirstLettre >> uv.x >> uv.y;
				tempUV.push_back(uv);
			}

			if (firstLetter == "vn")
			{
				Vector3D normal;
				findFirstLettre >> normal.x >> normal.y >> normal.z;
				tempNormal.push_back(normal);
			}
			if (firstLetter == "f")
			{
				int characterFindCounter = 0;

				while (findFirstLettre >> temp)
				{
					//Oragnise the numbers in the right place
					if (characterFindCounter == 0)
					{
						vectexPositionIndicies.push_back(temp);
					}
					else if (characterFindCounter == 1)
					{
						vertexTextureUVIndicies.push_back(temp);

					}
					else if (characterFindCounter == 2)
					{
						vectexNormalIndicies.push_back(temp);
					}

					//Ignore character
					if (findFirstLettre.peek() == '/')
					{
						++characterFindCounter;
						findFirstLettre.ignore(1, '/');
					}
					else if (findFirstLettre.peek() == ' ')
					{
						++characterFindCounter;
						findFirstLettre.ignore(1, ' ');
					}

					//Reset characterFindCounter
					if (characterFindCounter > 2)
					{
						characterFindCounter = 0;
					}
				}		
			}
		}

		vertexBFF.resize(vectexPositionIndicies.size(), Vertex());
		for (size_t i = 0; i < vertexBFF.size(); ++i)
		{
			vertexBFF[i].Position = tempVertices[vectexPositionIndicies[i] - 1];
			vertexBFF[i].TextureUV = tempUV[vertexTextureUVIndicies[i] - 1];
			vertexBFF[i].Normal = tempNormal[vectexNormalIndicies[i] - 1];
		}

		for (int i = 0; i < vertexBFF.size(); i++)
		{
			indexBFF.push_back(i);
		}

		VAO.Load(vertexBFF, indexBFF, VBO, EBO);

		//Debug for OBJloader
		/*for (int i = 0; i < vertexBFF.size(); i++)
		{
			printf("Position : %f, %f, %f \n", vertexBFF[i].Position.x, vertexBFF[i].Position.y, vertexBFF[i].Position.z);
		}

		for (int i = 0; i < vertexBFF.size(); i++)
		{
			printf("UV : % f, % f \n", vertexBFF[i].TextureUV.x, vertexBFF[i].TextureUV.y);
		}

		for (int i = 0; i < vertexBFF.size(); i++)
		{
			printf("Normal: %f, %f, %f \n", vertexBFF[i].Normal.x, vertexBFF[i].Normal.y, vertexBFF[i].Normal.z);
		}*/

	}
}