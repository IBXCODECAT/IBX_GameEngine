#pragma once

#include <stdio.h>

#ifdef IBX_PLATFORM_WINDOWS

extern IBX_Engine::Application* IBX_Engine::CreateApplication();

int main(int argc, char** argv)
{
	printf("IBX Engine\n");
	auto app = IBX_Engine::CreateApplication();
	app->Run();
	delete app;
}

#endif // IBX_PLATFORM_WINDOWS