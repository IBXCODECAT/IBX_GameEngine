#include "ibxpch.h"

#include "Application.h"

#include "IBX/Events//ApplicationEvent.h";
#include "IBX/Log.h";

namespace IBX_Engine
{
	Application::Application()
	{
		// Unique pointer allows for automatic memory management (no need to manually delete the pointer)
		m_Window = std::unique_ptr<Window>(Window::Create());
	}

	Application::~Application()
	{
	}

	
	void Application::Run()
	{
		while (true)
		{
			m_Window->OnUpdate();
		}
	}
}