#include <Shader.h>

void Resources::Shader::LoadShaders(int& shaderProgram)
{
	bool loadTrue = true;
	int success;
	char infoLog[512];

	std::string line;
	std::string src;
	std::ifstream file;

	// build and compile our shader program
	// ------------------------------------
	// vertex shader

	file.open("Resources/Shaders/vertexShader.glsl");
	if (file.is_open())
	{
		while (getline(file, line))
		{
			src += line + "\n";
		}
	}

	file.close();

	int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	const char* vertexShaderSource = src.c_str();
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	// check for shader compile errors
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	src = "";
	line = "";

	// fragment shader
	file.open("Resources/Shaders/fragShader.glsl");
	if (file.is_open())
	{
		while (getline(file, line))
		{
			src += line + "\n";
		}
	}

	file.close();

	int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	const char* fragmentShaderSource = src.c_str();
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);
	// check for shader compile errors
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	// link shaders
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	// check for linking errors
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}