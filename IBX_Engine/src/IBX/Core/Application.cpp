#include "ibxpch.h"

#include "Application.h"

// Include renderer API
#include "IBX/Renderer/Renderer.h"

#include "IBX/Core/Input/Input.h"

// TEMPORARY
#include <GLFW/glfw3.h>

namespace IBX_Engine
{

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)
	
	Application* Application::s_Instance = nullptr;

	Application::Application()
	{
		IBX_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;

		// Create the window
		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));
		
		Renderer::Init();

		auto m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);
	}

	Application::~Application()
	{

	}


	void Application::OnEvent(Event& e)
	{
		// Uncomment for debugging
		//	IBX_CORE_TRACE("{0}", e);

		EventDispatcher dispatcher(e);

		// Tell the dispatcher if it sees a WindowCloseEvent to call the OnWindowClose function
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));

		// Tell the dispatcher if it sees a WindowResizeEvent to call the OnWindowResize function
		dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_FN(OnWindowResize));

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
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* overlay)
	{
		m_LayerStack.PushOverlay(overlay);

		overlay->OnAttach();
	}

	void Application::Run()
	{
		while (m_Running)
		{
			float time = (float)glfwGetTime(); // Platform::GetTime()

			Timestep timestep = time - m_LastFrameTime;
			m_LastFrameTime = time;

			// If the application is not minimized, update all layers
			if (!m_Minimized)
			{
				// Update all layers (from bottom to top)
				for (Layer* layer : m_LayerStack)
					layer->OnUpdate(timestep); // Update the layer
			}

			m_ImGuiLayer->BeginNewFrame();

			// Update imgui on all layers (from bottom to top)
			for (Layer* layer : m_LayerStack)
				layer->OnImGuiRender(); // Draw ImGui

			m_ImGuiLayer->EndCurrentFrame();

			// Update the window
			m_Window->OnUpdate();
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		// Set m_Running to false to stop the application loop
		m_Running = false;
		return true;
	}

	bool Application::OnWindowResize(WindowResizeEvent& e)
	{
		// If the window is minimized or has no pixels, return false
		if (e.GetWidth() == 0 || e.GetHeight() == 0)
		{
			m_Minimized = true;
			return false;
		}

		m_Minimized = false;

		// Resize the viewport
		Renderer::OnWindowResize(e.GetWidth(), e.GetHeight());

		return false;
	}
}