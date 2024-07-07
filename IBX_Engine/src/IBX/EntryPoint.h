#pragma once

#include <stdio.h>

#ifdef IBX_PLATFORM_WINDOWS

extern IBX_Engine::Application* IBX_Engine::CreateApplication();

int main(int argc, char** argv)
{
	IBX_Engine::Log::Initialize();
	IBX_CORE_DEBUG("Initialized Core Logger!");
	IBX_CLIENT_DEBUG("Initialized Client Logger!");

	IBX_PROFILE_BEGIN_SESSION("Startup", "IBX_Profile-Startup.json");
	auto app = IBX_Engine::CreateApplication();
	IBX_PROFILE_END_SESSION();

	IBX_PROFILE_BEGIN_SESSION("Runtime", "IBX_Profile-Runtime.json");
	app->Run();
	IBX_PROFILE_END_SESSION();

	IBX_PROFILE_BEGIN_SESSION("Shutdown", "IBX_Profile-Shutdown.json");
	delete app;
	IBX_PROFILE_END_SESSION();
}

#endif // IBX_PLATFORM_WINDOWS