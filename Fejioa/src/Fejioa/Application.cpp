#include "fjpch.h"
#include "Application.h"

#include "Fejioa/Events/ApplicationEvent.h"
#include "Fejioa/Log.h"

#include <GLFW/glfw3.h>

namespace Fejioa
{
	Application::Application()
	{
		m_Window = std::unique_ptr<Window>(Window::Create());
	}

	Application::~Application()
	{
	}

	void Fejioa::Application::Run()
	{
		while (m_Running)
		{
			glClearColor(1, 0, 1, 1);
			glClear(GL_COLOR_BUFFER_BIT);
			m_Window->OnUpdate();
		}
	}
}
