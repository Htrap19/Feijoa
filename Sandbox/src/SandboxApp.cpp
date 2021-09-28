#include <Feijoa.h>
#include <Feijoa/Core/EntryPoint.h>

#include "Sandbox3D.h"

class SandboxApp : public Feijoa::Application
{
public:
	SandboxApp()
	{
		PushLayer(new Sandbox3D);
	}

	~SandboxApp()
	{
	}
};

Feijoa::Application* Feijoa::CreateApplication()
{
	return new SandboxApp();
}