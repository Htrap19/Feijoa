#include <Feijoa.h>
#include <Feijoa/Core/EntryPoint.h>

#include "ExampleLayer.h"
#include "Sandbox2D.h"

class SandboxApp : public Feijoa::Application
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

Feijoa::Application* Feijoa::CreateApplication()
{
	return new SandboxApp();
}