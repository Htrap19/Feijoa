#include <Fejioa.h>

class ExampleLayer : public Fejioa::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
	{
	}

	void OnUpdate() override
	{
		FJ_INFO("ExampleLayer::Update");
	}

	void OnEvent(Fejioa::Event& e)
	{
		FJ_TRACE("{0}", e);
	}
};

class SandboxApp : public Fejioa::Application
{
public:
	SandboxApp()
	{
		PushLayer(new ExampleLayer());
	}

	~SandboxApp()
	{
	}
};

Fejioa::Application* Fejioa::CreateApplication()
{
	return new SandboxApp();
}