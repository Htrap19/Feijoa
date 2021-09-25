#include "fjpch.h"
#include "Feijoa/Core/Input.h"

#ifdef FJ_PLATFORM_WINDOWS
#include "Platform/Windows/WindowsInput.h"
#endif

namespace Feijoa
{
	Scope<Input> Input::s_Instance = Input::Create();

	Scope<Input> Input::Create()
	{
#ifdef FJ_PLATFORM_WINDOWS
		return CreateScope<WindowsInput>();
#endif

		FJ_CORE_ASSERT(false, "Unknown platform!");
		return nullptr;
	}
}