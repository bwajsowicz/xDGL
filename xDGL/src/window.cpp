#include "window.h"

Window::Window(const unsigned int width, const unsigned int height, 
	const char *title, WindowMode windowMode)
{
	glfwInit();
	setHints();

	window = glfwCreateWindow(width, height, title,
		(windowMode == FULLSCREEN) ? glfwGetPrimaryMonitor() : nullptr, nullptr);

	if (window == nullptr)
	{
		throw "Failed to create GLFW window.";
	}

	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		throw "Failed to initialize GLAD.";

	glEnable(GL_MULTISAMPLE);
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
	glfwWindowHint(GLFW_SAMPLES, 4);
}

void Window::framebufferSizeCallback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

Window::~Window() {	glfwDestroyWindow(window); }
