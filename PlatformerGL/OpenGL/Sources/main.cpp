
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <App.h>
#include <Log.h>
#include <Mesh.h>
#include <ResourcesManager.h>
#include <Shader.h>

class Entity : public Model
{
public:
	vector<unique_ptr<Entity>> children;
	Entity* parent;
};

using namespace Core;
using namespace Resources;
using namespace LowRenderer;
using namespace Core::Debug;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);


void APIENTRY glDebugOutput(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam)
{
	// ignore non-significant error/warning codes
	if (id == 131169 || id == 131185 || id == 131218 || id == 131204) return;

	std::cout << "---------------" << std::endl;
	std::cout << "Debug message (" << id << "): " << message << std::endl;

	switch (source)
	{
	case GL_DEBUG_SOURCE_API:             std::cout << "Source: API"; break;
	case GL_DEBUG_SOURCE_WINDOW_SYSTEM:   std::cout << "Source: Window System"; break;
	case GL_DEBUG_SOURCE_SHADER_COMPILER: std::cout << "Source: Shader Compiler"; break;
	case GL_DEBUG_SOURCE_THIRD_PARTY:     std::cout << "Source: Third Party"; break;
	case GL_DEBUG_SOURCE_APPLICATION:     std::cout << "Source: Application"; break;
	case GL_DEBUG_SOURCE_OTHER:           std::cout << "Source: Other"; break;
	} std::cout << std::endl;

	switch (type)
	{
	case GL_DEBUG_TYPE_ERROR:               std::cout << "Type: Error"; break;
	case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: std::cout << "Type: Deprecated Behaviour"; break;
	case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:  std::cout << "Type: Undefined Behaviour"; break;
	case GL_DEBUG_TYPE_PORTABILITY:         std::cout << "Type: Portability"; break;
	case GL_DEBUG_TYPE_PERFORMANCE:         std::cout << "Type: Performance"; break;
	case GL_DEBUG_TYPE_MARKER:              std::cout << "Type: Marker"; break;
	case GL_DEBUG_TYPE_PUSH_GROUP:          std::cout << "Type: Push Group"; break;
	case GL_DEBUG_TYPE_POP_GROUP:           std::cout << "Type: Pop Group"; break;
	case GL_DEBUG_TYPE_OTHER:               std::cout << "Type: Other"; break;
	} std::cout << std::endl;

	switch (severity)
	{
	case GL_DEBUG_SEVERITY_HIGH:         std::cout << "Severity: high"; break;
	case GL_DEBUG_SEVERITY_MEDIUM:       std::cout << "Severity: medium"; break;
	case GL_DEBUG_SEVERITY_LOW:          std::cout << "Severity: low"; break;
	case GL_DEBUG_SEVERITY_NOTIFICATION: std::cout << "Severity: notification"; break;
	} std::cout << std::endl;
	std::cout << std::endl;
}

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int main()
{
	AppInitializer init =
	{
		1800, 1200,
		4,5,
		"ChatChien",
		framebuffer_size_callback,
		glDebugOutput
	};
	App app;
	Log log;
	Model* model;
	Model* Rabbit;
	Model* MF;
	Model* Darius;
	Model* Warwick;
	Model* WarwickPortal;
	Model* coin;
	Shader shader;
	Matrix4 mat4;
	Matrix4 mat42;
	ResourcesManager manager;
	app.Init(init);

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(app.window, true);
	ImGui_ImplOpenGL3_Init("#version 330");

	manager.CreateResource<Model>("cube", "Resources/Obj/cube1.obj");
	manager.CreateResource<Model>("MF", "Resources/Obj/MF.obj");
	model = manager.GetResource<Model>("cube");
	MF = manager.GetResource<Model>("MF");
	shader.LoadShaders(shader.shaderProgram);
	
	app.pointLights.push_back(new PointLight(Vector3D(0, 20, -10), Vector3D(1, 1, 1), 1, 0.022f, 0.0019f));
	app.directLights.push_back(new DirectionnalLight(Vector3D(0, 0, -1), Vector3D(1, 1, 1)));
	app.spotLights.push_back(new SpotLight(Vector3D(0, -10, 0), Vector3D(0, 0, 0), Vector3D(1, 1, 1), 1, 0.022f, 0.0019f, M_PI / 3.15));

	app.mesh.push_back(new Mesh(MF,Vector3D(0, 3.3f, 0), Vector3D(0, 3, 0), Vector3D(0.1, 0.1, 0.1), "Resources/Textures/mf.png"));

	app.mesh.push_back(new Mesh(model, Vector3D(0, 3, 0.6), Vector3D(0, -2, 0), Vector3D(50, 1, 15), "Resources/Textures/Bricks.png"));
	app.mesh.push_back(new Mesh(model, Vector3D(0, 4.7, 0), Vector3D(0, 0, -70), Vector3D(15, 1, 15), "Resources/Textures/Bricks.png"));
	app.mesh.push_back(new Mesh(model, Vector3D(1.564, 4.7, 1.5), Vector3D(0, 0, -82), Vector3D(15, 1, 15), "Resources/Textures/Bricks.png"));
	app.mesh.push_back(new Mesh(model, Vector3D(1.564, 4.7, 0), Vector3D(15, 0, -70), Vector3D(15, 1, 15), "Resources/Textures/Bricks.png"));
	app.mesh.push_back(new Mesh(model, Vector3D(0, 4.7, 0), Vector3D(-30, 0, -70), Vector3D(5, 1, 6), "Resources/Textures/Bricks.png"));
	app.mesh.push_back(new Mesh(model, Vector3D(0, 5, 0), Vector3D(-40, 0, -53), Vector3D(3, 1, 6), "Resources/Textures/Bricks.png"));
	app.mesh.push_back(new Mesh(model, Vector3D(0, 4.7, 0), Vector3D(-60, 0, -65), Vector3D(10, 2, 7), "Resources/Textures/Bricks.png"));
	app.mesh.push_back(new Mesh(model, Vector3D(0, 4.7, -6), Vector3D(-60, -0.9, -80), Vector3D(7, 1, 4), "Resources/Textures/Bricks.png"));
	app.mesh.push_back(new Mesh(model, Vector3D(0, 4.7, 0), Vector3D(-60, -10, -123), Vector3D(7, 1, 4), "Resources/Textures/Bricks.png"));
	app.mesh.push_back(new Mesh(model, Vector3D(0, 4.7, 0), Vector3D(-60, -13, -105), Vector3D(7, 1, 4), "Resources/Textures/Bricks.png"));
	app.mesh.push_back(new Mesh(model, Vector3D(0, 4.7, 0), Vector3D(-60, -15, -90), Vector3D(7, 1, 4), "Resources/Textures/Bricks.png"));

	app.SphereColl();

	// create a sampler and parameterize it
	// ------------------------------------
	GLuint sampler = 0;
	glGenSamplers(1, &sampler);
	glSamplerParameteri(sampler, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glSamplerParameteri(sampler, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glSamplerParameteri(sampler, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glSamplerParameteri(sampler, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glSamplerParameterf(sampler, GL_TEXTURE_MAX_ANISOTROPY_EXT, 4.f);

	GLint max = 0;
	glGetIntegerv(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS, &max);


	//glBindTextureUnit(0, texture);
	glBindSampler(0, sampler);


	// render loop
	// -----------
	while (!glfwWindowShouldClose(app.window))
	{
		app.Update(shader.shaderProgram);
	}

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	// uncomment this call to draw in wireframe polygons.
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	app.mesh.clear();

	glDeleteSamplers(1, &sampler);


	return 0;
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}