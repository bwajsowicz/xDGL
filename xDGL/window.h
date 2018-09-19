#include "stdafx.h"

#define OPENGL_VERSION_MAJOR 3
#define OPENGL_VERSION_MINOR 3

enum WindowMode
{
	FULLSCREEN,
	WINDOWED
};

class Window
{
public:
	Window(const unsigned int width, const unsigned int height, 
		const char *title, WindowMode windowMode);
	
	bool isWindowActive();

	GLFWwindow *getWindow();

private:
	GLFWwindow* window;

	void setHints();

	static void framebufferSizeCallback(GLFWwindow* window, int width, int height);

	~Window();
};