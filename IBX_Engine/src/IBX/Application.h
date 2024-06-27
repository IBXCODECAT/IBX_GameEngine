#pragma once

#include "Core.h"

#include "IBX/Events//Event.h"
#include "IBX/Events//ApplicationEvent.h"

#include "IBX/Layers/LayerStack.h"
#include "IBX/ImGui/ImGuiLayer.h"

#include "Window.h"

namespace IBX_Engine
{
	class IBX_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);

		// Add a layer to the layer stack (Layers are added in the order they are pushed)
		void PushLayer(Layer* layer);

		// Add an overlay to the layer stack (Overlays are added after the layers)
		void PushOverlay(Layer* overlay);

		// Static function to get the window instance
		inline Window& GetWindow() { return *m_Window; }

		// Static function to get the application instance
		inline static Application& Get() { return *s_Instance; }


	private:

		// Static pointer to the application instance
		static Application* s_Instance;

		bool OnWindowClose(WindowCloseEvent& e);

		// Unique pointer allows for automatic memory management (no need to manually delete the pointer)
		std::unique_ptr<Window> m_Window;

		ImGuiLayer* m_ImGuiLayer;

		// Wether or not the application is running (if false, the application will close)
		bool m_Running = true;

		// LayerStack is owned by the application
		LayerStack m_LayerStack;

	private:
		unsigned int m_VertexArray, m_VertexBuffer, m_IndexBuffer;
	};

	// To be defined in CLIENT
	Application* CreateApplication();
}