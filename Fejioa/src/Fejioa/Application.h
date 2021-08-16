#pragma once

#include "Core.h"
#include "Window.h"
#include "Events/ApplicationEvent.h"

namespace Fejioa
{
	class FEJIOA_API Application
	{
	public:
		Application();
		~Application();

		void Run();
		
		void OnEvent(Event& e);
	private:
		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
	};

	// To be defined in the CLIENT
	Application* CreateApplication();
}
