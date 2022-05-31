#include <App.h>
#include <Camera.h>

using namespace Core;
using namespace LowRenderer;

Camera camera;

void App::Init(AppInitializer init)
{
	// glfw: initialize and configure
	// ------------------------------
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, init.major);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, init.minor);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);

	// glfw window creation
	// --------------------
	window = glfwCreateWindow(init.width, init.height, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, init.framebuffer_size_callback);

	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return;
	}


	GLint flags = 0;
	glGetIntegerv(GL_CONTEXT_FLAGS, &flags);
	if (flags & GL_CONTEXT_FLAG_DEBUG_BIT)
	{
		glEnable(GL_DEBUG_OUTPUT);
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
		glDebugMessageCallback(init.glDegugOutput, nullptr);
		glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
	}
	glEnable(GL_DEPTH_TEST);

}

void App::Update(int shaderProgram)
{
	glfwPollEvents();
	processInput(window);

	Matrix4 PV;
	Matrix4 matrix4;

	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glClear(GL_DEPTH_BUFFER_BIT);	

	camera.camRight = camera.camUP.CrossProduct(camera.camFront);
	camera.camRight.Normalize();

	camera.viewMatrix = matrix4.LookAt(camera.camPos, camera.camPos + camera.camFront, camera.camUP);
	camera.projectionMatrix = matrix4.GetProjection(80.f, 0.005f, 100.f);
	PV = camera.projectionMatrix * camera.viewMatrix;
	
	glUseProgram(shaderProgram);
	
	glUniform3f(glGetUniformLocation(shaderProgram, "camPos"), camera.camPos.x, camera.camPos.y, camera.camPos.z);

	if (DirectionalLight)
	{
		PointLightsToShaders(shaderProgram);
	}
	if (PointLight)
	{
		DirectLightsToShaders(shaderProgram);
	}
	if (SpotLight)
	{
		SpotLightsToShaders(shaderProgram);
	}
	

	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	if (drawModel)
	{
		for (int i = 0; i < mesh.size(); i++)
		{
			mesh[i]->Update(shaderProgram, PV);
		}
	}
	
	static const char* item[]{ "Cube 1", "Cube 2", "MissFortune", "Darius", "WarWick", "Earth"};
	static int selectItem = 0;

	if (ImGui::Begin("Config"))
	{
		ImGui::Combo("Model List", &selectItem, item, IM_ARRAYSIZE(item));

		if (ImGui::CollapsingHeader("Draw", ImGuiTreeNodeFlags_DefaultOpen))
		{
			ImGui::Checkbox("All Model", &drawModel);
		}
		if (ImGui::CollapsingHeader("Transform", ImGuiTreeNodeFlags_DefaultOpen))
		{
			if (ImGui::CollapsingHeader("Rotation", ImGuiTreeNodeFlags_DefaultOpen))
			{
				ImGui::SliderFloat("Rotation X", &mesh[selectItem]->rot.x, 0, M_PI * 2);
				ImGui::SliderFloat("Rotation Y", &mesh[selectItem]->rot.y, 0, M_PI * 2);
				ImGui::SliderFloat("Rotation Z", &mesh[selectItem]->rot.z, 0, M_PI * 2);
			}
			if (ImGui::CollapsingHeader("Position", ImGuiTreeNodeFlags_DefaultOpen))
			{
				ImGui::SliderFloat("Position X", &mesh[selectItem]->pos.x, -20, 20);
				ImGui::SliderFloat("Position Y", &mesh[selectItem]->pos.y, -20, 20);
				ImGui::SliderFloat("Position Z", &mesh[selectItem]->pos.z, -20, 20);
			}
			if (ImGui::CollapsingHeader("Scale", ImGuiTreeNodeFlags_DefaultOpen))
			{
				ImGui::SliderFloat("Scale X", &mesh[selectItem]->scl.x, 0, 50);
				ImGui::SliderFloat("Scale Y", &mesh[selectItem]->scl.y, 0, 50);
				ImGui::SliderFloat("Scale Z", &mesh[selectItem]->scl.z, 0, 50);
			}
		}
		
	}
	ImGui::End();

	if (ImGui::Begin("Light Config"))
	{
		if (ImGui::CollapsingHeader("Light", ImGuiTreeNodeFlags_DefaultOpen))
		{
			if (ImGui::CollapsingHeader("Directionnal", ImGuiTreeNodeFlags_DefaultOpen))
			{
				ImGui::Checkbox("DirectionalLight", &PointLight);

				ImGui::SliderFloat("Directional Light\n Intensity", &directLights[0]->diffuseColor.x, 0, 1);
			}
			if (ImGui::CollapsingHeader("Point", ImGuiTreeNodeFlags_DefaultOpen))
			{
				ImGui::Checkbox("PointLight", &DirectionalLight);

				ImGui::SliderFloat("Point Light Intensity", &pointLights[0]->diffuseColor.y, 0, 1);
			}
			if (ImGui::CollapsingHeader("Spot", ImGuiTreeNodeFlags_DefaultOpen))
			{
				ImGui::Checkbox("SpotLight", &SpotLight);

				ImGui::SliderFloat("Spot Light Intensity", &spotLights[0]->diffuseColor.z, 0, 1);
			}
		}
	}
	
	ImGui::End();

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	glfwSwapBuffers(window);
}

void App::DirectLightsToShaders(unsigned int shaderProgram)
{

	for (int i = 0; i < directLights.size(); i++)
	{
		diffuseColor << "directLights[" << i << "].diffuseColor";
		ambientColor << "directLights[" << i << "].ambientColor";
		specularColor << "directLights[" << i << "].specularColor";
		lightDir << "directLights[" << i << "].direction";

		glUniform3f(glGetUniformLocation(shaderProgram, diffuseColor.str().c_str()), directLights[i]->diffuseColor.x, directLights[i]->diffuseColor.y, directLights[i]->diffuseColor.z);
		glUniform3f(glGetUniformLocation(shaderProgram, ambientColor.str().c_str()), directLights[i]->ambientColor.x, directLights[i]->ambientColor.y, directLights[i]->ambientColor.z);
		glUniform3f(glGetUniformLocation(shaderProgram, specularColor.str().c_str()), directLights[i]->specularColor.x, directLights[i]->specularColor.y, directLights[i]->specularColor.z);
		glUniform3f(glGetUniformLocation(shaderProgram, lightDir.str().c_str()), directLights[i]->direction.x, directLights[i]->direction.y, directLights[i]->direction.z);

		diffuseColor.str("");
		ambientColor.str("");
		specularColor.str("");
		lightDir.str("");
	}

	glUniform1i(glGetUniformLocation(shaderProgram, "directLightCount"), directLights.size());

}

void App::PointLightsToShaders(unsigned int shaderProgram)
{

	for (int i = 0; i < pointLights.size(); i++)
	{
		diffuseColor << "pointLights[" << i << "].diffuseColor";
		ambientColor << "pointLights[" << i << "].ambientColor";
		specularColor << "pointLights[" << i << "].specularColor";

		constant << "pointLights[" << i << "].constant";
		linear << "pointLights[" << i << "].linear";
		quadratic << "pointLights[" << i << "].quadratic";

		lightPos << "pointLights[" << i << "].position";

		glUniform3f(glGetUniformLocation(shaderProgram, diffuseColor.str().c_str()), pointLights[i]->diffuseColor.x, pointLights[i]->diffuseColor.y, pointLights[i]->diffuseColor.z);
		glUniform3f(glGetUniformLocation(shaderProgram, ambientColor.str().c_str()), pointLights[i]->ambientColor.x, pointLights[i]->ambientColor.y, pointLights[i]->ambientColor.z);
		glUniform3f(glGetUniformLocation(shaderProgram, specularColor.str().c_str()), pointLights[i]->specularColor.x, pointLights[i]->specularColor.y, pointLights[i]->specularColor.z);

		glUniform1f(glGetUniformLocation(shaderProgram, constant.str().c_str()), pointLights[i]->constant);
		glUniform1f(glGetUniformLocation(shaderProgram, linear.str().c_str()), pointLights[i]->linear);
		glUniform1f(glGetUniformLocation(shaderProgram, quadratic.str().c_str()), pointLights[i]->quadratic);

		glUniform3f(glGetUniformLocation(shaderProgram, lightPos.str().c_str()), pointLights[i]->position.x, pointLights[i]->position.y, pointLights[i]->position.z);

		diffuseColor.str("");
		ambientColor.str("");
		specularColor.str("");

		constant.str("");
		linear.str("");
		quadratic.str("");

		lightPos.str("");
	}

	glUniform1i(glGetUniformLocation(shaderProgram, "pointLightCount"), pointLights.size());

}

void App::SpotLightsToShaders(unsigned int shaderProgram)
{

	for (int i = 0; i < spotLights.size(); i++)
	{
		ambientColor << "spotLights[" << i << "].ambientColor";
		diffuseColor << "spotLights[" << i << "].diffuseColor";
		specularColor << "spotLights[" << i << "].specularColor";

		constant << "spotLights[" << i << "].constant";
		linear << "spotLights[" << i << "].linear";
		quadratic << "spotLights[" << i << "].quadratic";

		lightPos << "spotLights[" << i << "].position";
		lightDir << "spotLights[" << i << "].direction";
		lightAng << "spotLights[" << i << "].angle";

		glUniform3f(glGetUniformLocation(shaderProgram, diffuseColor.str().c_str()), spotLights[i]->diffuseColor.x, spotLights[i]->diffuseColor.y, spotLights[i]->diffuseColor.z);
		glUniform3f(glGetUniformLocation(shaderProgram, ambientColor.str().c_str()), spotLights[i]->ambientColor.x, spotLights[i]->ambientColor.y, spotLights[i]->ambientColor.z);
		glUniform3f(glGetUniformLocation(shaderProgram, specularColor.str().c_str()), spotLights[i]->specularColor.x, spotLights[i]->specularColor.y, spotLights[i]->specularColor.z);

		glUniform1f(glGetUniformLocation(shaderProgram, constant.str().c_str()), spotLights[i]->constant);
		glUniform1f(glGetUniformLocation(shaderProgram, linear.str().c_str()), spotLights[i]->linear);
		glUniform1f(glGetUniformLocation(shaderProgram, quadratic.str().c_str()), spotLights[i]->quadratic);

		glUniform3f(glGetUniformLocation(shaderProgram, lightPos.str().c_str()), spotLights[i]->position.x, spotLights[i]->position.y, spotLights[i]->position.z);
		glUniform3f(glGetUniformLocation(shaderProgram, lightDir.str().c_str()), spotLights[i]->direction.x, spotLights[i]->direction.y, spotLights[i]->direction.z);
		glUniform1f(glGetUniformLocation(shaderProgram, lightAng.str().c_str()), spotLights[i]->angle);

		diffuseColor.str("");
		ambientColor.str("");
		specularColor.str("");

		constant.str("");
		linear.str("");
		quadratic.str("");

		lightPos.str("");
		lightDir.str("");
		lightAng.str("");

	}

	glUniform1i(glGetUniformLocation(shaderProgram, "spotLightCount"), spotLights.size());
}


// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void App::processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		camera.camPos = camera.camPos + camera.moveSpeed * camera.camFront;
	}
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		camera.camPos = camera.camPos - camera.moveSpeed * camera.camFront;
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		camera.camPos = camera.camPos + camera.moveSpeed * camera.camRight;
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		camera.camPos = camera.camPos - camera.moveSpeed * camera.camRight;
	}
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		camera.camPos = camera.camPos + camera.moveSpeed * camera.camUP;
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE)
	{
		camera.moveSpeed = 0.1f;

	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
	{
		camera.moveSpeed = 0.5f;

	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
	{
		camera.camPos = camera.camPos - camera.moveSpeed * camera.camUP;
	}

	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
	{
		camera.mouseMove = true;
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	}
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_RELEASE)
	{
		camera.mouseMove = false;
		camera.firstMouse = true;
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}

	double x, y;
	glfwGetCursorPos(window, &x, &y);
	camera.CameraWithMouse(window, x, y);
}

App::~App()
{
	// glfw: terminate, clearing all previously allocated GLFW resources.
	// ------------------------------------------------------------------
	glfwTerminate();
}