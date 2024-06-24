#include "ibxpch.h"

#include "Application.h"

#include "IBX/Log.h";

#include <Glad/glad.h>

#include "Input.h"

namespace IBX_Engine
{

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)
	
	Application* Application::s_Instance = nullptr;

	Application::Application()
	{
		IBX_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;

		// Unique pointer allows for automatic memory management (no need to manually delete the pointer)
		m_Window = std::unique_ptr<Window>(Window::Create());

		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));
	}

	Application::~Application()
	{
	}


	void Application::OnEvent(Event& e)
	{
		// Uncomment for debugging
		IBX_CORE_TRACE("{0}", e);

		EventDispatcher dispatcher(e);

		// Tell the dispatcher if it sees a WindowCloseEvent to call the OnWindowClose function
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));

		// Go backwards through the layer stack and call OnEvent for each layer
		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();)
		{
			(*--it)->OnEvent(e);

			// If the event has been handled, break out of the loop
			// If overlays handle the event, the layers should not recieve the event
			if (e.Handled())
				break;
		}

	}
	
	void Application::PushLayer(Layer* layer)
	{
		IBX_CORE_INFO("Pushing layer: {0}", layer->GetName());
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* overlay)
	{
		IBX_CORE_INFO("Pushing overlay: {0}", overlay->GetName());
		m_LayerStack.PushOverlay(overlay);

		overlay->OnAttach();
	}

	void Application::Run()
	{
		while (m_Running)
		{
			// Clear the screen
			glClearColor(1, 0, 1, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			// Update all layers (from bottom to top)
			for (Layer* layer : m_LayerStack)
				layer->OnUpdate();

			// Update the window
			m_Window->OnUpdate();

			auto [x, y] = Input::GetMousePosition();
			IBX_CORE_TRACE("Mouse Input Test {0}, {1}", x, y);
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		// Set m_Running to false to stop the application loop
		m_Running = false;
		return true;
	}
}