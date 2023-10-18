#pragma once
#include "Graphics.h"
#include <map>

class Scene
{
public:
	Scene();
	~Scene();

	void LoadScene(std::string file);
	void UnloadScene();
	void ReloadScene();
	bool ValidateScene(std::string file);
	void DrawScene(Graphics* pgfx);
	bool CheckDependency(std::string path);
	inline std::string GetPath() const noexcept { return scene_path; }

private:
	std::vector<Mesh> mAssets;
	std::vector<Shader> mShaders;

	Camera mSceneCamera;
	std::string scene_path;

	std::map<int, int> mShaderModelBind;
};