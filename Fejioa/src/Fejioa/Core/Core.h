#pragma once

#include <memory>

#ifdef FJ_PLATFORM_WINDOWS
	#ifdef FJ_DYNAMIC_LINK
		#ifdef FJ_BUILD_DLL
			#define FEJIOA_API __declspec(dllexport)
		#else
			#define FEJIOA_API __declspec(dllimport)
		#endif
	#else
		#define FEJIOA_API
	#endif
#else
	#error Fejioa only supports Windows!
#endif

#ifdef FJ_DEBUG
	#define FJ_ENABLE_ASSERTS
#endif

#ifdef FJ_ENABLE_ASSERTS
	#define FJ_ASSERT(x, ...) { if (!(x)) { FJ_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define FJ_CORE_ASSERT(x, ...) { if(!(x)) { FJ_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define FJ_ASSERT(x, ...)
	#define FJ_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)

#define FJ_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

namespace Fejioa
{
	template <typename T>
	using Scope = std::unique_ptr<T>;

	template <typename T>
	using Ref = std::shared_ptr<T>;
}