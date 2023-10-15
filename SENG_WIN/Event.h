#pragma once
#include "Core.h"

namespace SENG
{
	class Event {};

	enum class EventType
	{
		Unknown = 0,
		WindowResize = 1,
		SceneStart = 2,
		SceneEnd = 3,
		ShaderCompile = 4,
		ShaderSet = 5,
		MeshCreate = 6,
		MeshDraw = 7,
		CameraSet = 8,
		MeshLoad = 9,
	};

	enum QueueType
	{
		QueueType_None = 0,
		QueueType_Graphics = 1,
		QueueType_Input = 2,
		QueueType_Logic = 3,
		QueueType_All = 4,
	};

	inline std::map<EventType, Event*> g_GraphicsQueue;
	inline std::map<EventType, Event*> g_InputQueue;
	inline std::map<EventType, Event*> g_LogicQueue;
}