#include "Application.h"

#include "Fejioa/Events/ApplicationEvent.h"
#include "Fejioa/Log.h"

namespace Fejioa
{
	Application::Application()
	{
	}

	Application::~Application()
	{
	}

	void Fejioa::Application::Run()
	{
		WindowResizeEvent e(1280, 720);
		if (e.IsInCategory(EventCategoryApplication))
		{
			FJ_TRACE(e);
		}
		if (e.IsInCategory(EventCategoryInput))
		{
			FJ_TRACE(e);
		}

		while (true);
	}
}
