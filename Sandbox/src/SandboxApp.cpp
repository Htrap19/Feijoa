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
		if (Fejioa::Input::IsKeyPressed(FJ_KEY_TAB))
			FJ_TRACE("Tab key is pressed (Poll)!");
	}

	void OnEvent(Fejioa::Event& e)
	{
		if (e.GetEventType() == Fejioa::EventType::KeyPressed)
		{
			Fejioa::KeyPressedEvent& event = (Fejioa::KeyPressedEvent&)e;
			if (event.GetKeyCode() == FJ_KEY_TAB)
				FJ_TRACE("Tab key is pressed (Event)!");

			FJ_TRACE("{0}", (char)event.GetKeyCode());
		}
	}
};

class SandboxApp : public Fejioa::Application
{
public:
	SandboxApp()
	{
		PushLayer(new ExampleLayer());
		PushOverlay(new Fejioa::ImGuiLayer());
	}

	~SandboxApp()
	{
	}
};

Fejioa::Application* Fejioa::CreateApplication()
{
	return new SandboxApp();
}