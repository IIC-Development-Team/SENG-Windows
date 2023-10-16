#include "kernel.h"
#include "cuda_runtime.h"
#include "device_launch_parameters.h"

namespace EXT_CUDA
{
	__global__ void ProcessMesh(aiMesh** pMesh, std::vector<GEO_CUDA::TempMeshData>& outData)
	{
		int t = threadIdx.x;

		for (int i = 0; i < pMesh[t]->mNumVertices; i++)
		{
			glm::vec3 v;
			glm::vec2 u;

			v.x = pMesh[t]->mVertices[i].x;
			v.y = pMesh[t]->mVertices[i].y;
			v.z = pMesh[t]->mVertices[i].z;

			outData[t].verticies.push_back(v);

			if (pMesh[t]->mTextureCoords[0]) {
				u.x = (float)pMesh[t]->mTextureCoords[0][i].x;
				u.y = (float)pMesh[t]->mTextureCoords[0][i].y;

				outData[t].uv.push_back(u);
			}
		}

		for (int i = 0; i < pMesh[t]->mNumFaces; i++)
		{
			aiFace face = pMesh[t]->mFaces[i];
			for (int j = 0; j < face.mNumIndices; j++)
			{
				outData[t].indices.push_back(face.mIndices[j]);
			}
		}
	}

	bool IsCudaCapable()
	{
		return cudaSetDevice(0) == cudaSuccess;
	}

	bool CUDA_EXP LoadMultipleMeshes(aiMesh** aMeshes, size_t size, std::vector<GEO_CUDA::TempMeshData>& outData)
	{
		if (!IsCudaCapable() || size <= 0 || aMeshes == nullptr)
			return false;


		if (!outData.empty())
		{
			printf("WARNING! Non empty vector was passed, all data will be errased");
			outData.clear();
		}

		for (int i = 0; i < size; i++)
		{
			GEO_CUDA::TempMeshData emptyData;
			outData.push_back(emptyData);
		}
	}
}