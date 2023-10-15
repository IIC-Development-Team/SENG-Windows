#pragma once
#include "Exception.h"
#include "Application.h"

extern SENG::Application* SENG::CreateNewApp();
extern void SENG::SetProjectSettings();

int main(int argc, char** argv) try
{
	SENG::SetProjectSettings();
	const auto app = SENG::CreateNewApp();
	int ec = app->Run();
	delete app;
	return ec;
} catch (SENG::SengException& e)
{
	std::cout << e.what() << std::endl;
	return 1;
}