#pragma once
#include "Feijoa/Debug/Instrumentor.h"

#ifdef FJ_PLATFORM_WINDOWS

extern Feijoa::Application* Feijoa::CreateApplication();

int main(int argc, char* argv[])
{
	Feijoa::Log::Init();

	FJ_PROFILE_BEGIN_SESSION("Startup", "FejioaProfile-Startup.json");
	auto app = Feijoa::CreateApplication();
	FJ_PROFILE_END_SESSION();

	FJ_PROFILE_BEGIN_SESSION("Runtime", "FejioaProfile-Runtime.json");
	app->Run();
	FJ_PROFILE_END_SESSION();

	FJ_PROFILE_BEGIN_SESSION("Startup", "FejioaProfile-Shutdown.json");
	delete app;
	FJ_PROFILE_END_SESSION();
	return 0;
}

#endif