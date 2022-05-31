#include <Mesh.h>

#define STB_IMAGE_IMPLEMENTATION
#include <STB_Image/stb_image.h>

LowRenderer::Mesh::Mesh(Model* model, Vector3D Rotation, Vector3D Position, Vector3D Scale, const char* fileName, Matrix4* parent)
{

	modelOriginal = model;
	rot = Rotation;
	pos = Position;
	scl = Scale;
	par = parent;

	// glGenBuffers(1, &VBO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glGenVertexArrays(1, &VAO);

	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO);

	// generate the texture data
	// ------------------------------------


	//glNamedBufferData(VBO, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * model->getVertexBuffer().size(), model->getVertexBuffer().data(), GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint32_t) * model->getIndexBuffer().size(), model->getIndexBuffer().data(), GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	glEnableVertexAttribArray(0);
	// normal attribute
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	// texture coord attribute
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(5 * sizeof(float)));
	glEnableVertexAttribArray(2);

	int width, height, nrChannels;

	stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load(fileName, &width, &height, &nrChannels, 0);

	glGenTextures(1, &texture) ;
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);


	stbi_image_free(data);
}


LowRenderer::Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
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

	glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized

	glDrawElements(GL_TRIANGLES, modelOriginal->getVertexBuffer().size(), GL_UNSIGNED_INT, 0);
}


