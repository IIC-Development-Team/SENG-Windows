#pragma once


//Stdlib includes
#include <string>
#include <iostream>
#include <source_location>
#include <exception>
#include <sstream>
#include <map>
#include <fstream>
#include <vector>
#include <thread>
#include <future>

//Vendor includes
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <ini.h>
#include <glm/gtc/matrix_transform.hpp>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>


namespace SENG
{
	//Version of SENG
	constexpr const unsigned int mCoreVersion = 3;

	struct PROJECT_SETTINGS
	{
		//General settings
		std::string mProjectName = "Sandbox (WINDOWS)";

		//Window settings
		bool mResizeable = false; //Can window be resized at runtime
		uint16_t mWndSize[2] = { 800, 600 }; //Size of window in pixels (width, height)
		std::string mWndTitle = "Sandbox (WIN32/OPENGL) "; //Title of window
		
		//Render settings
		bool mMultisampling = true;
		int mSampleCount = 16;
	};

	inline PROJECT_SETTINGS g_Settings;
}

#ifdef _WINDLL
#define SENG_API __declspec(dllexport)
#else
#define SENG_API __declspec(dllimport)
#endif