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
		// IBX_CORE_TRACE("ExampleLayer::Update");

		if (IBX_Engine::Input::IsKeyPressed(IBX_KEY_TAB))
			IBX_CLIENT_TRACE("Tab key is pressed!");
	}

	void OnEvent(IBX_Engine::Event& event) override
	{
		// IBX_CORE_INFO("{0}", event);

		if (event.GetEventType() == IBX_Engine::EventType::KeyPressed)
		{
			IBX_Engine::KeyReleasedEvent& e = (IBX_Engine::KeyReleasedEvent&)event;
			IBX_CLIENT_TRACE("{0}", (char)e.GetKeyCode());
		}
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