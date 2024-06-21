#include <IBX_Engine.h>

class ExampleLayer : public IBX_Engine::Layer
{
public:
	ExampleLayer() : Layer("Example")
	{

	}

	void OnUpdate() override
	{
		IBX_CLIENT_INFO("ExampleLayer::Update");
	}

	void OnEvent(IBX_Engine::Event& event) override
	{
		IBX_CLIENT_TRACE("{0}", event);	
	}
};

class SandboxApp : public IBX_Engine::Application
{
public:
	SandboxApp()
	{
		PushLayer(new ExampleLayer());
	}

	~SandboxApp()
	{

	}
};

IBX_Engine::Application* IBX_Engine::CreateApplication()
{
	return new SandboxApp();
}