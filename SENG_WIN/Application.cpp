#include "Application.h"
#include "Exception.h"

void SENG::SetProjectSettings()
{
	mINI::INIFile cfg_file("gameconf.ini");
	mINI::INIStructure config;
	bool f = cfg_file.read(config);
	if (!f)
		throw SengException();

	g_Settings.mWndSize[0] = std::stoi(config["Window"]["Width"]);
	g_Settings.mWndSize[1] = std::stoi(config["Window"]["Height"]);
	g_Settings.mProjectName = config["Project"]["Name"];
	g_Settings.mWndTitle = config["Window"]["Title"];
	g_Settings.mResizeable = std::stoi(config["Window"]["Resizeable"]);
	g_Settings.mMultisampling = std::stoi(config["Graphics"]["Multisample"]);
	g_Settings.mSampleCount = std::stoi(config["Graphics"]["SampleCount"]);
}

SENG::Application::Application()
{
	pWindow = new Window();
	pGraphics = new Graphics();
}

SENG::Application::~Application()
{
	delete pGraphics;
	delete pWindow;
}

bool SENG::Application::UpdateWindow()
{
	return pWindow->UpdateWindow();
}

void SENG::Application::HandleEvent(QueueType qt)
{
	if (qt == QueueType_Input || qt == QueueType_All)
	{
		for (const auto& ev : g_InputQueue)
		{
		}
		g_InputQueue.clear();
	}
	if (qt == QueueType_Logic || qt == QueueType_All)
	{
		for (const auto& ev : g_LogicQueue)
		{
		}
		g_LogicQueue.clear();
	}
}

void SENG::Application::CompileShader(Shader& shader, std::string vpath, std::string fpath)
{
	shader.fpath = fpath;
	shader.vpath = vpath;
	pGraphics->OnShaderCompile(shader);
}

void SENG::Application::SetShader(Shader& shader)
{
	pGraphics->OnShaderSet(shader);
}

void SENG::Application::MakeTriangle(Mesh& mesh)
{
	mesh.geom = std::vector<glm::vec3>{
		glm::vec3(-1,-1,0),
		glm::vec3(1,-1,0),
		glm::vec3(0,1,0),
	};
	mesh.color = std::vector<glm::vec3>{
		glm::vec3(1,0,0),
		glm::vec3(0,1,0),
		glm::vec3(0,0,1),
	};

	pGraphics->OnMeshCreate(mesh);
}

void SENG::Application::DrawMesh(Mesh& mesh)
{
	pGraphics->OnMeshDraw(mesh);
}

void SENG::Application::StartRender()
{
	pGraphics->OnSceneStart();
}

void SENG::Application::SetCamera(Camera camera)
{
	pGraphics->OnSetCamera(camera);
}

void SENG::Application::EndRender()
{
	pGraphics->OnSceneEnd(pWindow->GetWindowPointer());
}

void SENG::Application::LoadMeshFromFile(Mesh& mesh, std::string file)
{
	pGraphics->OnMeshLoad(file, mesh);

	for (int i = 0; i < mesh.geom.size(); i++)
	{
		mesh.color.push_back(glm::vec3(1,1,0));
	}

	pGraphics->OnMeshCreate(mesh);
}

inline void SENG::Application::AddEventToQueue(QueueType qt, EventType et, Event* pEvent)
{
	switch (qt)
	{
	case SENG::QueueType_Graphics:
		g_GraphicsQueue.emplace(et, pEvent);
		break;
	case SENG::QueueType_Input:
		g_InputQueue.emplace(et, pEvent);
		break;
	case SENG::QueueType_Logic:
		g_LogicQueue.emplace(et, pEvent);
		break;
	}
}
