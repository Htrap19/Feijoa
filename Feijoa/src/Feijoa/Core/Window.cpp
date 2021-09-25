#include "fjpch.h"
#include "Window.h"

#ifdef FJ_PLATFORM_WINDOWS
#include "Platform/Windows/WindowsWindow.h"
#endif

namespace Feijoa
{
	Scope<Window> Window::Create(const WindowProps& props /* = WindowProps() */)
	{
#ifdef FJ_PLATFORM_WINDOWS
		return CreateScope<WindowsWindow>(props);
#endif
		FJ_CORE_ASSERT(false, "Unknown platform");
		return nullptr;
	}
}