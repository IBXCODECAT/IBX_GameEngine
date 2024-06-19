#include <IBX_Engine.h>

class SandboxApp : public IBX_Engine::Application
{
public:
	SandboxApp()
	{

	}

	~SandboxApp()
	{

	}
};

IBX_Engine::Application* IBX_Engine::CreateApplication()
{
	return new SandboxApp();
}