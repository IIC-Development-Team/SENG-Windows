#pragma once
#include "Core.h"
#include "Graphics.h"

namespace SENG
{
	class SENG_API Scene
	{
	public:
		Scene(std::string file);
		void DrawScene(Graphics* pgfx);

	private:
		std::vector<Mesh> mAssets;
		std::vector<Shader> mShaders;

		Camera mSceneCamera;

		std::map<int, int> mShaderModelBind;
	};
}