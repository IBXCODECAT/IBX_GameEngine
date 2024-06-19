#pragma once

#include "Core.h"

namespace IBX_Engine
{
	class IBX_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	};

	// To be defined in CLIENT
	Application* CreateApplication();
}