#include "Graphics.h"
#include "Exception.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_include.h>
#include <stb_image.h>

void SENG::Graphics::ProcessMesh(aiMesh* pMesh, const aiScene* scene, SENG::Mesh& mesh)
{
	for (int i = 0; i < pMesh->mNumVertices; i++)
	{
		glm::vec3 v;
		glm::vec2 t;

		v.x = pMesh->mVertices[i].x;
		v.y = pMesh->mVertices[i].y;
		v.z = pMesh->mVertices[i].z;

		mesh.geom.push_back(v);

		if (pMesh->mTextureCoords[0]) {
			t.x = (float)pMesh->mTextureCoords[0][i].x;
			t.y = (float)pMesh->mTextureCoords[0][i].y;

			mesh.uv.push_back(t);
		}
	}

	for (int i = 0; i < pMesh->mNumFaces; i++)
	{
		aiFace face = pMesh->mFaces[i];
		for (int j = 0; j < face.mNumIndices; j++)
		{
			mesh.indices.push_back(face.mIndices[j]);
		}
	}
}

void SENG::Graphics::ProcessNode(aiNode* node, const aiScene* scene, SENG::Mesh& mesh)
{
	for (int i = 0; i < node->mNumMeshes; i++) {
		aiMesh* pMesh = scene->mMeshes[node->mMeshes[i]];
		ProcessMesh(pMesh, scene, mesh);
	}

	for (int i = 0; i < node->mNumChildren; i++) {
		ProcessNode(node->mChildren[i], scene, mesh);
	}
}

void SENG::Graphics::OnSceneStart()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.2f, 0.6f, 1.0f);
}

void SENG::Graphics::OnSceneEnd(GLFWwindow* wnd)
{
	glfwSwapBuffers(wnd);
}

void SENG::Graphics::OnShaderCompile(Shader& shader)
{
	GLuint Vertex = glCreateShader(GL_VERTEX_SHADER);
	GLuint Fragment = glCreateShader(GL_FRAGMENT_SHADER);

	std::ifstream vfile(shader.vpath);
	if (!vfile.is_open())
		throw SengException();

	std::ostringstream vstream;
	vstream << vfile.rdbuf();
	std::string vcode = vstream.str();
	vfile.close();

	std::ifstream ffile(shader.fpath);
	if (!ffile.is_open())
		throw SengException();

	std::ostringstream fstream;
	fstream << ffile.rdbuf();
	std::string fcode = fstream.str();
	ffile.close();

	GLint result = GL_FALSE;
	int InfoLen;

	printf("Compiling shader: %s\n", shader.vpath.c_str());
	char const* vsptr = vcode.c_str();
	glShaderSource(Vertex, 1, &vsptr, nullptr);
	glCompileShader(Vertex);
	glGetShaderiv(Vertex, GL_COMPILE_STATUS, &result);
	glGetShaderiv(Vertex, GL_INFO_LOG_LENGTH, &InfoLen);
	if (InfoLen > 0) {
		std::vector<char> ShaderErrMsg(InfoLen + 1);
		glGetShaderInfoLog(Vertex, InfoLen, NULL, &ShaderErrMsg[0]);
		printf("Compilation error: %s\n", &ShaderErrMsg[0]);
		throw SengException();
	}

	printf("Compiling shader: %s\n", shader.fpath.c_str());
	char const* fsptr = fcode.c_str();
	glShaderSource(Fragment, 1, &fsptr, nullptr);
	glCompileShader(Fragment);
	glGetShaderiv(Fragment, GL_COMPILE_STATUS, &result);
	glGetShaderiv(Fragment, GL_INFO_LOG_LENGTH, &InfoLen);
	if (InfoLen > 0) {
		std::vector<char> ShaderErrMsg(InfoLen + 1);
		glGetShaderInfoLog(Fragment, InfoLen, NULL, &ShaderErrMsg[0]);
		printf("Compilation error: %s\n", &ShaderErrMsg[0]);
		throw SengException();
	}

	printf("Linking shaders...\n");
	GLuint prog = glCreateProgram();
	glAttachShader(prog, Vertex);
	glAttachShader(prog, Fragment);
	glLinkProgram(prog);

	glGetProgramiv(prog, GL_LINK_STATUS, &result);
	glGetProgramiv(prog, GL_INFO_LOG_LENGTH, &InfoLen);
	if (InfoLen > 0) {
		std::vector<char> ShaderErrMsg(InfoLen + 1);
		glGetProgramInfoLog(Fragment, InfoLen, NULL, &ShaderErrMsg[0]);
		printf("Linking error: %s\n", &ShaderErrMsg[0]);
		throw SengException();
	}

	glDetachShader(prog, Vertex);
	glDetachShader(prog, Fragment);

	glDeleteShader(Vertex);
	glDeleteShader(Fragment);

	shader.program = prog;
}

void SENG::Graphics::OnShaderSet(Shader& shader)
{
	mMatID = glGetUniformLocation(shader.program, "MVP");
	mColSamp = glGetUniformLocation(shader.program, "myTextureSampler");
	glUseProgram(shader.program);
}

void SENG::Graphics::OnMeshCreate(Mesh& mesh)
{
	glGenVertexArrays(1, &mesh.VArray);
	glBindVertexArray(mesh.VArray);

	glGenBuffers(1, &mesh.VBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, mesh.VBuffer);
	glBufferData(GL_ARRAY_BUFFER, mesh.geom.size() * sizeof(glm::vec3), &mesh.geom[0], GL_STATIC_DRAW);
	
	if (!mesh.color.empty())
	{
		glGenBuffers(1, &mesh.CBuffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.CBuffer);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh.color.size() * sizeof(glm::vec3), &mesh.color[0], GL_STATIC_DRAW);
	}

	if (!mesh.indices.empty())
	{
		glGenBuffers(1, &mesh.IBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, mesh.IBuffer);
		glBufferData(GL_ARRAY_BUFFER, mesh.indices.size() * sizeof(unsigned int), &mesh.indices[0], GL_STATIC_DRAW);
	}

	if (!mesh.uv.empty())
	{
		glGenBuffers(1, &mesh.UBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, mesh.UBuffer);
		glBufferData(GL_ARRAY_BUFFER, mesh.uv.size() * sizeof(glm::vec2), &mesh.uv[0], GL_STATIC_DRAW);
	}

	mesh.mInitalized = true;
}

void SENG::Graphics::OnMeshDraw(Mesh& mesh)
{
	if (mesh.mInitalized == true)
	{
		if (mesh.mMat.mColor.mTexBuffer != 0)
		{
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, mesh.mMat.mColor.mTexBuffer);
			glUniform1i(mColSamp, 0);
		}

		glm::mat4 MVP = mProjection * mView * mesh.GetWolrdMatrix();
		glUniformMatrix4fv(mMatID, 1, GL_FALSE, &MVP[0][0]);
		glBindVertexArray(mesh.VArray);
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, mesh.VBuffer);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

		if (!mesh.color.empty())
		{
			glEnableVertexAttribArray(1);
			glBindBuffer(GL_ARRAY_BUFFER, mesh.CBuffer);
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
		}

		if (!mesh.uv.empty())
		{
			glEnableVertexAttribArray(2);
			glBindBuffer(GL_ARRAY_BUFFER, mesh.UBuffer);
			glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
		}

		if (!mesh.indices.empty())
		{
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.IBuffer);
			glDrawElements(GL_TRIANGLES, mesh.indices.size(), GL_UNSIGNED_INT, 0);
		}
		else
		{
			glDrawArrays(GL_TRIANGLES, 0, mesh.geom.size());
		}
		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);
		glBindVertexArray(0);
	}
	else
	{
		printf("Mesh not initalized yet...\n");
	}
}

void SENG::Graphics::OnSetCamera(Camera camera)
{
	mView = camera.GetViewMatrix();
	mProjection = camera.GetProjectionMatrix();
	mCameraSet = true;
}

void SENG::Graphics::OnMeshLoad(std::string file, Mesh& mesh)
{
	Assimp::Importer imp;

	const aiScene* pScene = imp.ReadFile(file, aiProcessPreset_TargetRealtime_Fast);
	if (pScene == nullptr)
		throw SengException();

	if (pScene->mNumMeshes <= 0)
		throw SengException();

	ProcessNode(pScene->mRootNode, pScene, mesh);
}

void SENG::Graphics::OnLoadTexture(Texture& tx)
{
	tx.rawData = stbi_load(tx.filename.c_str(), &tx.width, &tx.height, &tx.channels, 3);

	glGenTextures(1, &tx.mTexBuffer);
	glBindTexture(GL_TEXTURE_2D, tx.mTexBuffer);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, tx.width, tx.height, 0, GL_RGB, GL_UNSIGNED_BYTE, tx.rawData);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
}

void SENG::Mesh::AdjustPosition(float x, float y, float z)
{
	mPosition += glm::vec3(x, y, z);
	mWorld = glm::translate(mWorld, mPosition);
}

void SENG::Mesh::SetRotation(float x, float y, float z)
{
	mRotation = glm::vec3(x, y, z);
	mWorld = glm::rotate(mWorld, glm::radians(x), glm::vec3(1, 0, 0));
	mWorld = glm::rotate(mWorld, glm::radians(y), glm::vec3(0, 1, 0));
	mWorld = glm::rotate(mWorld, glm::radians(z), glm::vec3(0, 0, 1));
}

void SENG::Mesh::AdjustRotation(float x, float y, float z)
{
	mRotation += glm::vec3(x, y, z);
	mWorld = glm::rotate(mWorld, glm::radians(mRotation.x), glm::vec3(1, 0, 0));
	mWorld = glm::rotate(mWorld, glm::radians(mRotation.y), glm::vec3(0, 1, 0));
	mWorld = glm::rotate(mWorld, glm::radians(mRotation.z), glm::vec3(0, 0, 1));
}

void SENG::Mesh::SetScale(float x, float y, float z)
{
	mScale = glm::vec3(x, y, z);
	mWorld = glm::scale(mWorld, mScale);
}

void SENG::Mesh::AdjustScale(float x, float y, float z)
{
	mScale += glm::vec3(x, y, z);
	mWorld = glm::scale(mWorld, mScale);
}

void SENG::Mesh::SetPosition(float x, float y, float z)
{
	mPosition = glm::vec3(x, y, z);
	mWorld = glm::translate(mWorld, mPosition);
}

void SENG::Material::LoadColor(std::string file)
{
	mColor.filename = file;
	Graphics::OnLoadTexture(mColor);
}
