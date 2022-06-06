#include <Mesh.h>

#define STB_IMAGE_IMPLEMENTATION
#include <STB_Image/stb_image.h>

LowRenderer::Mesh::Mesh(Model* model, Vector3D Rotation, Vector3D Position, Vector3D Scale, const char* fileName )
{

	modelOriginal = model;
	rot = Rotation;
	pos = Position;
	scl = Scale;

	int width, height, nrChannels;

	stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load(fileName, &width, &height, &nrChannels, 0);

	glGenTextures(1, &texture) ;
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);


	stbi_image_free(data);
}



void LowRenderer::Mesh::Update(unsigned int shaderProgram, Matrix4 PVMatrix)
{
	Matrix4 modelMatrix = ModelMatrixPop();
	Matrix4 MVP = PVMatrix * modelMatrix;

	glUseProgram(shaderProgram);

	glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "MVP"), 1, GL_FALSE, &MVP.matrixTab4[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "Model"), 1, GL_FALSE, &modelMatrix.matrixTab4[0][0]);

	// draw our first triangle
	glBindTextureUnit(0, texture);
	glUniform1i(glGetUniformLocation(shaderProgram, "texture1"), 0); // set it manually

	glBindVertexArray(modelOriginal->VAO.vao); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized

	glDrawElements(GL_TRIANGLES, modelOriginal->vertexBFF.size(), GL_UNSIGNED_INT, 0);
}


