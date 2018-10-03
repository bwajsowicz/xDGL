#include "stdafx.h"

#include "window.h"
#include "camera.h"
#include "resource_manager.h"

#ifdef _DEBUG
#include "debug.h"
#endif

void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
const char *WIN_TITLE = "xDGL";

// camera
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

// timing
float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;

void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

int main()
{


	Window *window;
	try
	{
		 window = new Window(SCR_WIDTH, SCR_HEIGHT, WIN_TITLE, WINDOWED);
	}
	catch (const char *msg)
	{
		std::cerr << msg << std::endl;
		return EXIT_FAILURE;
	}

	glfwSetCursorPosCallback(window->getWindow(), mouse_callback);
	glfwSetScrollCallback(window->getWindow(), scroll_callback);

	#ifdef _DEBUG
	printDebugData();
	#endif

	glEnable(GL_DEPTH_TEST);

	const char *vertexShaderPath = "resources/shaders/vertex/basic.vert";
	const char *fragmentShaderPath = "resources/shaders/fragment/basic.frag";

	Shader basic = ResourceManager::LoadShader(vertexShaderPath, fragmentShaderPath , nullptr, "basic");
	Texture2D test_texture = ResourceManager::LoadTexture("resources/textures/kitku.jpg", true, "test_texture");

	float vertices[] = {
		-0.5f, 0.0f, -0.5f, 0.0f, 0.0f, // bottom left
		 0.5f, 0.0f, -0.5f, 1.0f, 0.0f, // bottom right,
		-0.5f, 0.0f,  0.5f, 0.0f, 1.0f, // upper left,

		 0.5f, 0.0f, -0.5f, 1.0f, 0.0f, // bottom right
		 0.5f, 0.0f,  0.5f, 1.0f, 1.0f, // upper right
		-0.5f, 0.0f,  0.5f, 0.0f, 1.0f, // upper left

		-0.5f, 0.0f, -0.5f, 0.0f, 0.0f, // bottom left
		 0.5f, 0.0f, -0.5f, 1.0f, 0.0f, // bottom right,
		 0.0f, 0.5f,  0.0f, 0.5f, 1.0f, // center top

		 0.5f, 0.0f, -0.5f, 0.0f, 0.0f, // bottom right
		 0.5f, 0.0f,  0.5f, 1.0f, 0.0f, // upper right
		 0.0f, 0.5f,  0.0f, 0.5f, 1.0f, // center top

		 0.5f, 0.0f,  0.5f, 0.0f, 0.0f, // upper right
		 -0.5f, 0.0f,  0.5f, 1.0f, 0.0f, // upper left
		  0.0f, 0.5f,  0.0f, 0.5f, 1.0f, // center top

		 -0.5f, 0.0f,  0.5f, 0.0f, 0.0f, // upper left
		 -0.5f, 0.0f, -0.5f, 1.0f, 0.0f, // bottom left
		  0.0f, 0.5f, 0.0f, 0.5f, 1.0f // center top
	};

	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);

	glm::mat4 projection = glm::mat4(1.0f);
	projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH/SCR_HEIGHT, 0.1f, 100.0f);
	
	while (!glfwWindowShouldClose(window->getWindow()))
	{
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		processInput(window->getWindow());

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		float timeValue = glfwGetTime();
		float colorValue = sin(timeValue);

		//std::cout << glm::radians((float)glfwGetTime())*100.0f << std::endl;
	
		glm::mat4 view = glm::mat4(1.0f);
		view = camera.GetViewMatrix();

		glm::mat4 model = glm::mat4(1.0f);
		//model = glm::rotate(model, glm::radians((float)glfwGetTime())*100.0f, glm::vec3(1.0f, 0.0f, 0.0f));
		//model = glm::rotate(model, glm::radians((float)glfwGetTime())*100.0f, glm::vec3(0.0f, 1.0f, 0.0f));

		basic.Use();
		basic.SetMatrix4("model", model);
		basic.SetMatrix4("view", view);
		basic.SetMatrix4("projection", projection);
		test_texture.Bind();
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 18);

		glfwSwapBuffers(window->getWindow());
		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

	glfwTerminate();

	return 0;
}

void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.ProcessKeyboard(FORWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.ProcessKeyboard(BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.ProcessKeyboard(LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.ProcessKeyboard(RIGHT, deltaTime);
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos;

	lastX = xpos;
	lastY = ypos;

	camera.ProcessMouseMovement(xoffset, yoffset);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll(yoffset);
}