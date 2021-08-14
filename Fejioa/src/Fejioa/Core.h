#pragma once

#ifdef FJ_PLATFORM_WINDOWS
	#ifdef FJ_BUILD_DLL
		#define FEJIOA_API __declspec(dllexport)
	#else
		#define FEJIOA_API __declspec(dllimport)
	#endif
#else
	#error Fejioa only supports Windows!
#endif

#define BIT(x) (1 << x)