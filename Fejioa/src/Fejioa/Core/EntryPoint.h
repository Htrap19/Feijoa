#pragma once
#include "Fejioa/Core/Core.h"

#ifdef FJ_PLATFORM_WINDOWS

extern Fejioa::Application* Fejioa::CreateApplication();

int main(int argc, char* argv[])
{
	Fejioa::Log::Init();
	FJ_CORE_WARN("Initialized Log!");
	int a = 5;
	FJ_INFO("Hello var={0}", a);

	auto app = Fejioa::CreateApplication();
	app->Run();
	delete app;
	return 0;
}

#endif