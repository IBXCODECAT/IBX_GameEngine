#include "Application.h"

#include "IBX/Events//ApplicationEvent.h";
#include "IBX/Log.h";

namespace IBX_Engine
{
	Application::Application()
	{
	}

	Application::~Application()
	{
	}

	
	void Application::Run()
	{
		WindowResizeEvent e(1280, 720);


		if(e.IsInCategory(EventCategoryApplication))
		{
			IBX_CORE_TRACE(e);
		}

		if(e.IsInCategory(EventCategoryInput))
		{
			IBX_CORE_TRACE(e);
		}

		while (true);
	}
}