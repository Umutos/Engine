#include <Model.h>
#include <iostream>

namespace Resources
{

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