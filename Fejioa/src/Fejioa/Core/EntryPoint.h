#pragma once
#include "Fejioa/Core/Base.h"

#ifdef FJ_PLATFORM_WINDOWS

extern Fejioa::Application* Fejioa::CreateApplication();

int main(int argc, char* argv[])
{
	Fejioa::Log::Init();

	FJ_PROFILE_BEGIN_SESSION("Startup", "FejioaProfile-Startup.json");
	auto app = Fejioa::CreateApplication();
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