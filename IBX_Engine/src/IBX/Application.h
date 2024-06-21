#pragma once

#include "Core.h"

#include "IBX/Events//Event.h";
#include "IBX/Events//ApplicationEvent.h";

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

	private:

		bool OnWindowClose(WindowCloseEvent& e);

		// Unique pointer allows for automatic memory management (no need to manually delete the pointer)
		std::unique_ptr<Window> m_Window;

		bool m_Running = true;
	};

	// To be defined in CLIENT
	Application* CreateApplication();
}