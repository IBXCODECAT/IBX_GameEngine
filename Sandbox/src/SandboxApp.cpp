#include <IBX_Engine.h>

class ExampleLayer : public IBX_Engine::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
	{
	}

	void OnUpdate() override
	{
		IBX_CORE_TRACE("ExampleLayer::Update");
	}

	void OnEvent(IBX_Engine::Event& event) override
	{
		IBX_CORE_INFO("{0}", event);
	}

};

class Sandbox : public IBX_Engine::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
		PushOverlay(new IBX_Engine::ImGuiLayer());
	}

	~Sandbox()
	{

	}

};

IBX_Engine::Application* IBX_Engine::CreateApplication()
{
	return new Sandbox();
}