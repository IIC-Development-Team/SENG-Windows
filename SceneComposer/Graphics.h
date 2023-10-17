#pragma once
#include "Window.h"
#include "Camera.h"
#include <glm/gtc/matrix_transform.hpp>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>


#pragma region CONCEPTS
	class Shader
	{
		friend class Graphics;
	public:
		std::string vpath, fpath;

	private:
		GLuint program = 0;
	};

	class Texture
	{
		friend class Graphics;
	public:
		std::string filename;
		unsigned char* rawData;
	private:
		int width, height, channels;
		GLuint mTexBuffer = 0;
	};

	class Material
	{
		friend class Graphics;
	private:
		Texture mColor, mNormal, mOcclussion, mSpecular;

	public:
		void LoadColor(std::string file);
	};

	class Mesh
	{
		friend class Graphics;
	public:
		std::vector<glm::vec3> geom;
		std::vector<glm::vec3> color;
		std::vector<glm::vec2> uv;
		std::vector<unsigned int> indices;
		inline glm::mat4 GetWolrdMatrix() const noexcept { return mWorld; }
		void SetPosition(float x, float y, float z);
		void AdjustPosition(float x, float y, float z);
		void SetRotation(float x, float y, float z);
		void AdjustRotation(float x, float y, float z);
		void SetScale(float x, float y, float z);
		void AdjustScale(float x, float y, float z);
		std::string name = "Default component";

	private:
		GLuint VBuffer = 0, VArray = 0, CBuffer = 0, IBuffer = 0, UBuffer = 0;
		glm::mat4 mWorld = glm::mat4(1.0f); //World matrix
		glm::vec3 mPosition = glm::vec3(0, 0, 0);
		glm::vec3 mRotation = glm::vec3(0, 0, 0);
		glm::vec3 mScale = glm::vec3(1, 1, 1);
		bool mInitalized = false;

	public:
		Material mMat;
	};

#pragma endregion

#pragma region CLASS

	class Graphics
	{
		friend class Material;
		friend class Scene;
	public:
		void OnSceneStart();
		void OnSceneEnd(GLFWwindow*);
		static void OnShaderCompile(Shader& shader);
		void OnShaderSet(Shader& shader);
		static void OnMeshCreate(Mesh& mesh);
		void OnMeshDraw(Mesh& mesh);
		void OnSetCamera(Camera camera);
		static void OnMeshLoad(std::string file, Mesh& mesh);
		static void OnLoadTexture(Texture& texture);
		glm::vec3 RayCastMouse(double mouse_x, double mouse_y, GLFWwindow* pwnd);

		static void ProcessNode(aiNode* node, const aiScene* scene, Mesh& mesh);
		static void ProcessMesh(aiMesh* pMesh, const aiScene* scene, Mesh& mesh);
	private:
		bool mCameraSet = false;
		GLuint mMatID = 0, mColSamp = 0;
		glm::mat4 mView = glm::mat4(), mProjection = glm::mat4();
	};

#pragma endregion