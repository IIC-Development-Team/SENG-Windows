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
	bool CUDA_EXP IsCudaCapable();
}