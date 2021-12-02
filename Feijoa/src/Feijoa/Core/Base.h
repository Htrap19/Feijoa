#pragma once

#include <memory>
#include "Feijoa/Core/PlatformDetection.h"

#ifdef FJ_DEBUG
	#if defined(FJ_PLATFORM_WINDOWS)
		#define FJ_DEBUGBREAK() __debugbreak();
	#elif defined(FJ_PLATFORM_LINUX)
		#include <signal.h>
		#define FJ_DEBUGBREAK() raise(SIGTRAP)
	#else
		#error "Platform doesn't support debugbreak yet!"
	#endif
	#define FJ_ENABLE_ASSERTS
#else
	#define FJ_DEBUGBREAK()
#endif

#define FJ_EXPAND_MACRO(x) x
#define FJ_STRINGIFY_MACRO(x) #x

#define BIT(x) (1 << x)

#define FJ_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

namespace Feijoa
{
	template <typename T>
	using Scope = std::unique_ptr<T>;

	template <typename T, typename ... Args>
	constexpr Scope<T> CreateScope(Args&& ... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

	template <typename T>
	using Ref = std::shared_ptr<T>;

	template <typename T, typename ... Args>
	constexpr Ref<T> CreateRef(Args&& ... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}
}

#include "Feijoa/Core/Log.h"
#include "Feijoa/Core/Assert.h"