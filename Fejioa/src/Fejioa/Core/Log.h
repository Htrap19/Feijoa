#pragma once

#include "Fejioa/Core/Base.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

namespace Fejioa
{
	class  Log
	{
	public:
		static void Init();

		inline static Ref<spdlog::logger> GetCoreLogger() { return s_CoreLogger; }
		inline static Ref<spdlog::logger> GetClientLogger() { return s_ClientLogger; }

	private:
		static Ref<spdlog::logger> s_CoreLogger;
		static Ref<spdlog::logger> s_ClientLogger;
	};
}

// Core log macros
#define FJ_CORE_ERROR(...)       ::Fejioa::Log::GetCoreLogger()->error(__VA_ARGS__)
#define FJ_CORE_WARN(...)        ::Fejioa::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define FJ_CORE_INFO(...)        ::Fejioa::Log::GetCoreLogger()->info(__VA_ARGS__)
#define FJ_CORE_TRACE(...)       ::Fejioa::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define FJ_CORE_CRITICAL(...)       ::Fejioa::Log::GetCoreLogger()->critical(__VA_ARGS__)

// Client log macros
#define FJ_ERROR(...)            ::Fejioa::Log::GetClientLogger()->error(__VA_ARGS__)
#define FJ_WARN(...)             ::Fejioa::Log::GetClientLogger()->warn(__VA_ARGS__)
#define FJ_INFO(...)             ::Fejioa::Log::GetClientLogger()->info(__VA_ARGS__)
#define FJ_TRACE(...)            ::Fejioa::Log::GetClientLogger()->trace(__VA_ARGS__)
#define FJ_CRITICAL(...)            ::Fejioa::Log::GetClientLogger()->critical(__VA_ARGS__)