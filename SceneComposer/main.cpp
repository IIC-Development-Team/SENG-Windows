#include "Window.h"
#include "loguru.hpp"
#include "Graphics.h"
#include "Scene.h"
#include <filesystem>
namespace fs = std::filesystem;

int main(int argc, char** argv)
{
	loguru::init(argc, argv);
	loguru::add_file("scenecomposer.log", loguru::FileMode::Append, loguru::Verbosity_0);

	LOG_F(INFO, "Scene Composer v1.0 by IIC Development team");
	LOG_F(INFO, "Using loguru by Emilk");

	Window window(1280, 720, "Scene Composer 1");
	Graphics* pgfx = new Graphics();

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
	ImGui_ImplGlfw_InitForOpenGL(window.GetWindowPointer(), true);
	ImGui_ImplOpenGL3_Init();

	Scene* pUsedScene = new Scene();
	pUsedScene->LoadScene("TestScene.ssf");


	while (true)
	{
		std::string scenename = "Current scene: " + pUsedScene->GetPath();

		if (window.UpdateWindow())
			break;
		pgfx->OnSceneStart();
		//Start rendering scene
		pUsedScene->DrawScene(pgfx);

		//Start rendering GUI
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		if (ImGui::Begin("Scene Manager"))
		{
			if (ImGui::CollapsingHeader("Found scenes"))
			{
				for (const auto& entry : fs::directory_iterator("./"))
				{
					std::string f = entry.path().string();
					if(f[f.length() - 1] == 'f')
						if(ImGui::CollapsingHeader(f.c_str()))
						{
							ImGui::Button("Load", ImVec2(40, 20));
							ImGui::SameLine();
							ImGui::Button("Validate", ImVec2(70, 20));
						}
				}
			}
			if (ImGui::CollapsingHeader(scenename.c_str()))
			{
				ImGui::Button("Reload", ImVec2(60, 20));
				ImGui::SameLine();
				ImGui::Button("Save", ImVec2(40, 20));
				ImGui::SameLine();
				ImGui::Button("Save as", ImVec2(60, 20));
			}
			ImGui::End();
		}

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		pgfx->OnSceneEnd(window.GetWindowPointer());
	}

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	return 0;
}