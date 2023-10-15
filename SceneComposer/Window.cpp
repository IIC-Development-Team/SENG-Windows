#include "Window.h"
#include "Exception.h"
#include "loguru.hpp"

void GLAPIENTRY
MessageCallback(GLenum source,
	GLenum type,
	GLuint id,
	GLenum severity,
	GLsizei length,
	const GLchar* message,
	const void* userParam)
{
	fprintf(stderr, "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n",
		(type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : ""),
		type, severity, message);
}

void GLFWERRCALLBACK(int a, const char* what)
{
	LOG_F(ERROR, "GLFW error: %s", what);
}

Window::Window(int width, int height, const char* name)
{
	if (!glfwInit())
		throw Exception();

	if (!glfwInit())
		throw Exception();

	glfwSetErrorCallback(GLFWERRCALLBACK);

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_SAMPLES, 16);

	pWindow = glfwCreateWindow(width, height,
		name, nullptr, nullptr);

	if (!pWindow)
	{
		throw Exception();
	}

	glfwMakeContextCurrent(pWindow);
	glewExperimental = true;

	if (glewInit() != GLEW_OK)
		throw Exception();

	glEnable(GL_DEBUG_OUTPUT);
	glDebugMessageCallback(MessageCallback, 0);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	glfwSwapInterval(0);

	glfwShowWindow(pWindow);
}

bool Window::UpdateWindow()
{
	glfwPollEvents();
	return glfwWindowShouldClose(pWindow);
}

Window::~Window()
{
	glfwDestroyWindow(pWindow);
	glfwTerminate();
}