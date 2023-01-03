#version 330 core
out vec4 FragColor;

in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;

uniform sampler2D texture1;
uniform sampler2D texture2; 

struct DirectionnalLight {
	vec3 direction;

	vec3 ambientColor;
	vec3 diffuseColor;
	vec3 specularColor;
};

struct PointLight {
	vec3 position;

	vec3 ambientColor;
	vec3 diffuseColor;
	vec3 specularColor;

	float constant;
	float linear;
	float quadratic;
};

struct SpotLight {
	vec3 position;
	vec3 direction;

	vec3 ambientColor;
	vec3 diffuseColor;
	vec3 specularColor;

	float constant;
	float linear;
	float quadratic;

	float angle;
};

uniform vec3 camPos;

uniform PointLight[8] pointLights;
uniform DirectionnalLight[8] directLights;
uniform SpotLight[8] spotLights;

uniform int pointLightCount;
uniform int directLightCount;
uniform int spotLightCount;

vec3 PointLightCalcul(PointLight light, vec3 normal, vec3 fragPos, vec3 camPos);
vec3 DirectLightCalcul(DirectionnalLight light, vec3 normal, vec3 fragPos, vec3 camPos);
vec3 SpotLightCalcul(SpotLight light, vec3 normal, vec3 fragPos, vec3 camPos);

void main()
{
	vec3 result = vec3(0, 0, 0);

	for (int i = 0; i < spotLightCount; i++)
		result += SpotLightCalcul(spotLights[i], Normal, FragPos, camPos);

	for (int i = 0; i < pointLightCount; i++)
		result += PointLightCalcul(pointLights[i], Normal, FragPos, camPos);

	for (int i = 0; i < directLightCount; i++)
		result += DirectLightCalcul(directLights[i], Normal, FragPos, camPos);

	FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), 0.5) * vec4(result, 1.0);
};

vec3 PointLightCalcul(PointLight light, vec3 normal, vec3 fragPos, vec3 camPos)
{
	vec3 ambient = light.ambientColor;

	//diffuse
	vec3 norm = normalize(normal);
	vec3 lightDir = normalize(light.position - fragPos);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * light.diffuseColor;

	//specular
	vec3 viewDir = normalize(camPos - fragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
	vec3 specular = spec * light.specularColor;

	//final
	float distance = length(light.position - FragPos);
	float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
	vec3 final = (ambient + diffuse + specular) * attenuation;

	return final;
};

vec3 DirectLightCalcul(DirectionnalLight light, vec3 normal, vec3 fragPos, vec3 camPos)
{
	vec3 ambient = light.ambientColor;

	//diffuse
	vec3 norm = normalize(normal);
	vec3 lightDir = normalize(-light.direction);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * light.diffuseColor;

	//specular
	vec3 viewDir = normalize(camPos - fragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
	vec3 specular = spec * light.specularColor;

	return (ambient + diffuse + specular);
};

vec3 SpotLightCalcul(SpotLight light, vec3 normal, vec3 fragPos, vec3 camPos)
{
	vec3 lightDir = normalize(light.position - fragPos);
	float theta = dot(lightDir, normalize(-light.direction));

	if (theta > light.angle)
	{
		vec3 ambient = light.ambientColor;

		vec3 norm = normalize(normal);
		float diff = max(dot(norm, lightDir), 0.0);
		vec3 diffuse = diff * light.diffuseColor;

		//specular
		vec3 viewDir = normalize(camPos - fragPos);
		vec3 reflectDir = reflect(-lightDir, norm);
		float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
		vec3 specular = spec * light.specularColor;

		//final
		float distance = length(light.position - FragPos);
		float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
		vec3 final = (ambient + diffuse + specular) * attenuation;

		return final;
	}
	else
	{
		float distance = length(light.position - FragPos);
		float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
		return light.ambientColor * attenuation;
	}
};