#pragma once
#include "Core.h"
#include "Window.h"
#include "Graphics.h"
#include "Event.h"

namespace SENG
{
	class SENG_API Application
	{
	public:
		Application();
		virtual ~Application();

		virtual int Run() = 0;

		bool UpdateWindow();
		void HandleEvent(QueueType qt);
		void CompileShader(Shader& shader, std::string vpath, std::string fpath);
		void SetShader(Shader& shader);
		void MakeTriangle(Mesh& mesh);
		void DrawMesh(Mesh& mesh);
		void StartRender();
		void SetCamera(Camera camera);
		void EndRender();
		void LoadMeshFromFile(Mesh& mesh, std::string file);
		inline void AddEventToQueue(QueueType qt, EventType et, Event* pEvent);
		inline Graphics* GetGfxInterface() noexcept { return pGraphics; }
	private:
		Window* pWindow;
		Graphics* pGraphics;
	};

	//NEEDS TO BE DEFINED IN CLIENT
	void SENG_API SetProjectSettings();
	Application* CreateNewApp();
}