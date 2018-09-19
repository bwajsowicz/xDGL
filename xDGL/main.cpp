#include "stdafx.h"

#include "window.h"

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
		fprintf(stderr, "%s\n", msg);
		return EXIT_FAILURE;
	}

	while (!glfwWindowShouldClose(window->getWindow()))
	{
		processInput(window->getWindow());

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glfwSwapBuffers(window->getWindow());
		glfwPollEvents();
	}

	glfwTerminate();

	return 0;
}

void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}