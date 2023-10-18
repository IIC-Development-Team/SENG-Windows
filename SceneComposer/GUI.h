#pragma once
#include "imgui/imgui.h"
#include "imgui/imconfig.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include "Scene.h"
#include <filesystem>

namespace fs = std::filesystem;

void DrawSceneManager(Scene* pUsedScene)
{
	std::string scenename = "Current scene: " + pUsedScene->GetPath();

	if (ImGui::Begin("Scene Manager"))
	{
		if (ImGui::CollapsingHeader("Found scenes"))
		{
			for (const auto& entry : fs::directory_iterator("./"))
			{
				std::string f = entry.path().string();
				if (f[f.length() - 1] == 'f')
					if (ImGui::CollapsingHeader(f.c_str()))
					{
						if (ImGui::Button("Load", ImVec2(40, 20)))
						{
							pUsedScene->UnloadScene();
							pUsedScene->LoadScene(f);
						}
						ImGui::SameLine();
						if (ImGui::Button("Validate", ImVec2(70, 20)))
						{
							pUsedScene->ValidateScene(f);
						}
					}
			}
		}
		if (ImGui::CollapsingHeader(scenename.c_str()))
		{
			if (ImGui::Button("Reload", ImVec2(60, 20)))
			{
				pUsedScene->ReloadScene();
			}
			ImGui::SameLine();
			ImGui::Button("Save", ImVec2(40, 20));
			ImGui::SameLine();
			ImGui::Button("Save as", ImVec2(60, 20));
		}
		ImGui::End();
	}
}