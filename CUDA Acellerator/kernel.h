#pragma once
#include <stdio.h>
#include <functional>
#include <vector>

#include <assimp/scene.h>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

#ifdef _WINDLL
#define CUDA_EXP __declspec(dllexport)
#else
#define CUDA_EXP __declspec(dllimport)
#endif

namespace EXT_CUDA
{
	namespace GEO_CUDA
	{
		struct TempMeshData
		{
			std::vector<glm::vec3> verticies;
			std::vector<glm::vec2> uv;
			std::vector<unsigned int> indices;
		};
	}

	bool CUDA_EXP IsCudaCapable();

	bool CUDA_EXP LoadMultipleMeshes(aiMesh** aMeshes, size_t size, std::vector<GEO_CUDA::TempMeshData>& outData);
}