#pragma once
#include "Core.h"

namespace SENG
{
	class SENG_API Window
	{
	public:
		Window();
		~Window();

		inline GLFWwindow* GetWindowPointer() const noexcept { return pWindow; }
		bool UpdateWindow();

	private:
		GLFWwindow* pWindow;
	};
}