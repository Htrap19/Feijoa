#pragma once

#include <memory>

#ifdef _WIN32
	#ifdef _WIN64
		#define FJ_PLATFORM_WINDOWS
	#else
		#error "x86 builds not supported"
	#endif // _WIN64
#elif defined(__APPLE__) || defined(__MACH__)
	#include "<TargetConditionals.h>"
	#if TARGET_IPHONE_SIMULATOR == 1
		#error "IOS simulator is not supported!"
	#elif TARGET_OS_IPHONE == 1
		#define FJ_PLATFORM_IOS
		#error "IOS is not supported!"
	#elif TARGET_OS_MAC == 1
		#define FJ_PLATFORM_MACOS
		#error "MacOS not supported!"
	#else
		#error "Unknown Apple platform!"
	#endif
#elif defined(__ANDROID__)
	#ifdef FJ_PLATFORM_ANDROID
		#define FJ_PLATFORM_ANDROID
	#endif
	#error "Android is not supported!"
#elif defined(__linux__)
	#ifdef FJ_PLATFORM_LINUX
		#define FJ_PLATFORM_LINUX
	#endif
	#error "Linux is not supported!"
#else
	#error "Unknown platform!"
#endif

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