#include <Fejioa.h>

class SandboxApp : public Fejioa::Application
{
public:
	SandboxApp()
	{
	}

	~SandboxApp()
	{
	}
};

Fejioa::Application* Fejioa::CreateApplication()
{
	return new SandboxApp();
}