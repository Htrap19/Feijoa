#pragma once

#include "Feijoa/Core/Base.h"

struct GLFWwindow;

namespace Feijoa
{
	class GraphicsContext
	{
	public:
		virtual void Init() = 0;
		virtual void SwapBuffers() = 0;

		static Scope<GraphicsContext> Create(GLFWwindow* window);
	};
}