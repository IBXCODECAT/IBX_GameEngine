#pragma once

#include <stdio.h>

#ifdef IBX_PLATFORM_WINDOWS

extern IBX_Engine::Application* IBX_Engine::CreateApplication();

int main(int argc, char** argv)
{
	IBX_Engine::Log::Initialize();
	
	IBX_CORE_DEBUG("Initialized Core Logger!");

	IBX_CLIENT_DEBUG("Initialized Client Logger!");

	auto app = IBX_Engine::CreateApplication();
	app->Run();
	delete app;
}

#endif // IBX_PLATFORM_WINDOWS