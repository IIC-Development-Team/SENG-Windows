#include "SENG.h"

class Sandbox : public SENG::Application
{
public:
	Sandbox();
	~Sandbox() override;

	int Run() override;

private:
	
};

SENG::Application* SENG::CreateNewApp()
{
	return new Sandbox();
}

Sandbox::Sandbox()
{

}

Sandbox::~Sandbox()
{
}

int Sandbox::Run()
{
	SENG::Scene mTestScene(std::string("TestScene.ssf"));

	while (true)
	{
		if (UpdateWindow())
			break;
		StartRender();
		mTestScene.DrawScene(GetGfxInterface());
		EndRender();
	}

	return 0;
}
