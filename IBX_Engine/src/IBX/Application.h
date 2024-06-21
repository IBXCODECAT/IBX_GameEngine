#pragma once

#include "Core.h"

#include "IBX/Events//Event.h";
#include "IBX/Events//ApplicationEvent.h";

#include "IBX/Layers/LayerStack.h";

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

	private:

		bool OnWindowClose(WindowCloseEvent& e);

		// Unique pointer allows for automatic memory management (no need to manually delete the pointer)
		std::unique_ptr<Window> m_Window;

		// Wether or not the application is running (if false, the application will close)
		bool m_Running = true;

		// LayerStack is owned by the application
		LayerStack m_LayerStack;
	};

	// To be defined in CLIENT
	Application* CreateApplication();
}