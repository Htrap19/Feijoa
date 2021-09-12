#include <Fejioa.h>
#include <Fejioa/Core/EntryPoint.h>

#include "ExampleLayer.h"
#include "Sandbox2D.h"


class SandboxApp : public Fejioa::Application
{
public:
	SandboxApp()
	{
		//PushLayer(new ExampleLayer());
		PushLayer(new Sandbox2D);
	}

	~SandboxApp()
	{
	}
};

Fejioa::Application* Fejioa::CreateApplication()
{
	return new SandboxApp();
}