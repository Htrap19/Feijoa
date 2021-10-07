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

#ifdef FJ_ENABLE_ASSERTS
	#define FJ_ASSERT(x, ...) { if (!(x)) { FJ_ERROR("Assertion Failed: {0}", __VA_ARGS__); FJ_DEBUGBREAK(); } }
	#define FJ_CORE_ASSERT(x, ...) { if(!(x)) { FJ_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); FJ_DEBUGBREAK(); } }
#else
	#define FJ_ASSERT(x, ...)
	#define FJ_CORE_ASSERT(x, ...)
#endif

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