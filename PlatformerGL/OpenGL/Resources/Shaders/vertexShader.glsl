#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec2 aTexCoord;
layout(location = 2) in vec3 aNormal;

out vec3 FragPos;
out vec2 TexCoord;
out vec3 Normal;

uniform mat4 MVP;
uniform mat4 Model;
 
void main()
{
	gl_Position = vec4(aPos, 1.0) * MVP;
	FragPos = vec3(vec4(aPos, 1.0) * Model);
	TexCoord = aTexCoord;
	Normal = aNormal * mat3(transpose(inverse(Model)));
}