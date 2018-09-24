#include "stdafx.h"

#include "window.h"
#include "resource_manager.h"

#ifdef _DEBUG
#include "debug.h"
#endif

void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
const char *WIN_TITLE = "xDGL";

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

	#ifdef _DEBUG
	printDebugData();
	#endif

	const char *vertexShaderPath = "resources/shaders/vertex/basic.vert";
	const char *fragmentShaderPath = "resources/shaders/fragment/basic.frag";

	Shader basic = ResourceManager::LoadShader(vertexShaderPath, fragmentShaderPath , nullptr, "basic");
	Texture2D test_texture = ResourceManager::LoadTexture("resources/textures/kitku.jpg", true, "test_texture");

	float vertices[] = {
		-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, // left  
		 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // right 
		 0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.5f, 1.0f  // top   
	};

	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);

	while (!glfwWindowShouldClose(window->getWindow()))
	{
		processInput(window->getWindow());

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		float timeValue = glfwGetTime();
		float colorValue = sin(timeValue);

		basic.Use();
		basic.SetVector4f("TestUniform", glm::vec4(colorValue, colorValue, colorValue, 0.0f));
		test_texture.Bind();
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);

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
}