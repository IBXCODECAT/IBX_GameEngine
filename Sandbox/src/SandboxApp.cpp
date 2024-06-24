#include <IBX_Engine.h>

#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
glm::mat4 camera(float Translate, glm::vec2 const& Rotate)
{
	glm::mat4 Projection = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.f);
	glm::mat4 View = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -Translate));
	View = glm::rotate(View, Rotate.y, glm::vec3(-1.0f, 0.0f, 0.0f));
	View = glm::rotate(View, Rotate.x, glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 Model = glm::scale(glm::mat4(1.0f), glm::vec3(0.5f));
	return Projection * View * Model;
}

class ExampleLayer : public IBX_Engine::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
	{
		auto cam = camera(5.0f, {0.5f, 0.5f });
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