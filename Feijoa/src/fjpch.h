#pragma once

#include "Feijoa/Core/PlatformDetection.h"

#ifdef FJ_PLATFORM_WINDOWS
	#ifndef NOMINMAX
		#define NOMINMAX
	#endif
#endif

#include <iostream>
#include <memory>
#include <utility>
#include <algorithm>
#include <functional>

#include <string>
#include <sstream>
#include <array>
#include <vector>
#include <unordered_map>
#include <unordered_set>

#include "Feijoa/Core/Base.h"
#include "Feijoa/Core/Log.h"
#include "Feijoa/Debug/Instrumentor.h"

#ifdef FJ_PLATFORM_WINDOWS
	#include <Windows.h>
#endif