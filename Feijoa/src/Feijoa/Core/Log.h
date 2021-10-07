#pragma once

#include "Feijoa/Core/Base.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

namespace Feijoa
{
	class Log
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
#define FJ_CORE_ERROR(...)       ::Feijoa::Log::GetCoreLogger()->error(__VA_ARGS__)
#define FJ_CORE_WARN(...)        ::Feijoa::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define FJ_CORE_INFO(...)        ::Feijoa::Log::GetCoreLogger()->info(__VA_ARGS__)
#define FJ_CORE_TRACE(...)       ::Feijoa::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define FJ_CORE_CRITICAL(...)       ::Feijoa::Log::GetCoreLogger()->critical(__VA_ARGS__)

// Client log macros
#define FJ_ERROR(...)            ::Feijoa::Log::GetClientLogger()->error(__VA_ARGS__)
#define FJ_WARN(...)             ::Feijoa::Log::GetClientLogger()->warn(__VA_ARGS__)
#define FJ_INFO(...)             ::Feijoa::Log::GetClientLogger()->info(__VA_ARGS__)
#define FJ_TRACE(...)            ::Feijoa::Log::GetClientLogger()->trace(__VA_ARGS__)
#define FJ_CRITICAL(...)            ::Feijoa::Log::GetClientLogger()->critical(__VA_ARGS__)