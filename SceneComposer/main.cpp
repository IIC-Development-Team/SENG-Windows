#include "Window.h"
#include "loguru.hpp"
#include "Graphics.h"
#include "Scene.h"
#include "GUI.h"

Window window(1280, 720, "Scene Composer 1");
Graphics* pgfx = new Graphics();
Scene* pUsedScene = new Scene();

int main(int argc, char** argv)
{
	loguru::init(argc, argv);
	loguru::add_file("scenecomposer.log", loguru::FileMode::Append, loguru::Verbosity_0);

	LOG_F(INFO, "Scene Composer v1.0 by IIC Development team");
	LOG_F(INFO, "Using loguru by Emilk");

	if (glfwRawMouseMotionSupported())
		glfwSetInputMode(window.GetWindowPointer(), GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
	ImGui_ImplGlfw_InitForOpenGL(window.GetWindowPointer(), true);
	ImGui_ImplOpenGL3_Init();

	pUsedScene->LoadScene("TestScene.ssf");

	while (true)
	{
		

		if (window.UpdateWindow())
			break;
		pgfx->OnSceneStart();
		//Start rendering scene
		pUsedScene->DrawScene(pgfx);
		//Start rendering GUI
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		DrawSceneManager(pUsedScene);


		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		pgfx->OnSceneEnd(window.GetWindowPointer());
	}

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	return 0;
}