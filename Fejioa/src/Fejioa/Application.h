#pragma once

#include "Core.h"

namespace Fejioa
{
	class FEJIOA_API Application
	{
	public:
		Application();
		~Application();

		void Run();
	};

	// To be defined in the CLIENT
	Application* CreateApplication();
}
