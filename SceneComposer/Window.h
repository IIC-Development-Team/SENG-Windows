#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include <ini.h>

class Window
{
public:
	Window(int width, int height, const char* name);
	~Window();

	inline GLFWwindow* GetWindowPointer() const noexcept { return pWindow; }
	bool UpdateWindow();

private:
	GLFWwindow* pWindow;
};