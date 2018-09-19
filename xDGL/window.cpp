#include "window.h"

Window::Window(const unsigned int width, const unsigned int height, 
	const char *title, WindowMode windowMode)
{
	glfwInit();
	setHints();

	window = glfwCreateWindow(width, height, title,
		(windowMode == FULLSCREEN) ? glfwGetPrimaryMonitor() : NULL, NULL);

	if (window == NULL)
	{
		printf("%s\n", "Failed to create GLFW window");
		glfwTerminate();
		//TODO: Implement function for handling different errors.
	}

	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		printf("%s\n", "Failed to initialize GLAD.");
		//TODO: Implement function for handling different errors.
	}
}

bool Window::isWindowActive() { return glfwWindowShouldClose(window); }

GLFWwindow *Window::getWindow()
{
	return window;
}

void Window::setHints()
{
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, OPENGL_VERSION_MAJOR);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, OPENGL_VERSION_MINOR);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

void Window::framebufferSizeCallback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

Window::~Window() {	glfwDestroyWindow(window); }
