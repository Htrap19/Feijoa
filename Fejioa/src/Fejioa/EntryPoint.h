#pragma once

#ifdef FJ_PLATFORM_WINDOWS

extern Fejioa::Application* Fejioa::CreateApplication();

int main(int argc, char* argv[])
{
	auto app = Fejioa::CreateApplication();
	app->Run();
	delete app;
	return 0;
}

#endif