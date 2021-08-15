#pragma once

#include "Core.h"
#include "Window.h"

namespace Fejioa
{
	class FEJIOA_API Application
	{
	public:
		Application();
		~Application();

		void Run();

	private:
		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
	};

	// To be defined in the CLIENT
	Application* CreateApplication();
}
