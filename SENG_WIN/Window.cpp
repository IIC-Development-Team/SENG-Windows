#include "Window.h"
#include "Window.h"
#include "Exception.h"

void GLAPIENTRY
MessageCallback(GLenum source,
	GLenum type,
	GLuint id,
	GLenum severity,
	GLsizei length,
	const GLchar* message,
	const void* userParam)
{
	if(type == GL_DEBUG_TYPE_ERROR)
	fprintf(stderr, "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n",
		(type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : ""),
		type, severity, message);
}

void GLFWERRCALLBACK(int a, const char* what)
{
	printf("GLFW error: %s", what);
}

SENG::Window::Window()
{
	if (!glfwInit())
		throw SengException();

	glfwSetErrorCallback(GLFWERRCALLBACK);

	if (!g_Settings.mResizeable)
		glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	if(g_Settings.mMultisampling)
		glfwWindowHint(GLFW_SAMPLES, g_Settings.mSampleCount);
	
	pWindow = glfwCreateWindow(g_Settings.mWndSize[0], g_Settings.mWndSize[1],
		g_Settings.mWndTitle.c_str(), nullptr, nullptr);

	if (!pWindow)
	{
		throw SengException();
	}

	glfwMakeContextCurrent(pWindow);
	glewExperimental = true;

	if (glewInit() != GLEW_OK)
		throw SengException();

	glEnable(GL_DEBUG_OUTPUT);
	glDebugMessageCallback(MessageCallback, 0);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	glfwSwapInterval(0);

	glfwShowWindow(pWindow);
}


SENG::Window::~Window()
{
	glfwDestroyWindow(pWindow);
	glfwTerminate();
}

bool SENG::Window::UpdateWindow()
{
	glfwPollEvents();
	return glfwWindowShouldClose(pWindow);
}
