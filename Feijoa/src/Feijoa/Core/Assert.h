#pragma once

#include "Feijoa/Core/Base.h"
#include "Feijoa/Core/Log.h"

#ifdef FJ_ENABLE_ASSERTS

	namespace Feijoa::Assert
	{
		constexpr const char* CurrentFileName(const char* path)
		{
			const char* file = path;
			while (*path)
			{
				if (*path == '/' || *path == '\\')
					file = ++path;
				else
					path++;
			}

			return file;
		}
	}

	#define FJ_INTERNAL_ASSERT_IMPL(type, check, msg, ...) { if (!(check)) { FJ##type##ERROR(msg, __VA_ARGS__); FJ_DEBUGBREAK(); } }
	#define FJ_INTERNAL_ASSERT_WITH_MSG(type, check, ...) FJ_INTERNAL_ASSERT_IMPL(type, check, "Assertion failed: {0}", __VA_ARGS__)
	#define FJ_INTERNAL_ASSERT_NO_MSG(type, check) FJ_INTERNAL_ASSERT_IMPL(type, check, "Asertion '{0}' failed at {1}:{2}", FJ_STRINGIFY_MACRO(check), ::Feijoa::Assert::CurrentFileName(__FILE__), __LINE__)

	#define FJ_INTERNAL_ASSERT_GET_MACRO_NAME(arg1, arg2, macro, ...) macro
	#define FJ_INTERNAL_ASSERT_GET_MACRO(...) FJ_EXPAND_MACRO( FJ_INTERNAL_ASSERT_GET_MACRO_NAME(__VA_ARGS__, FJ_INTERNAL_ASSERT_WITH_MSG, FJ_INTERNAL_ASSERT_NO_MSG) )

	#define FJ_ASSERT(...) FJ_EXPAND_MACRO( FJ_INTERNAL_ASSERT_GET_MACRO(__VA_ARGS__)(_, __VA_ARGS__) )
	#define FJ_CORE_ASSERT(...) FJ_EXPAND_MACRO( FJ_INTERNAL_ASSERT_GET_MACRO(__VA_ARGS__)(_CORE_, __VA_ARGS__) )

#else
	#define FJ_ASSERT(...)
	#define FJ_CORE_ASSERT(...)

#endif