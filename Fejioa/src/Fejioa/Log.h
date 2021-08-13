#pragma once

#include "Core.h"
#include "spdlog/spdlog.h"

namespace Fejioa
{
	class FEJIOA_API Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger> GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger> GetClientLogger() { return s_ClientLogger; }

	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};
}

// Core log macros
#define FJ_CORE_ERROR(...)       ::Fejioa::Log::GetCoreLogger()->error(__VA_ARGS__)
#define FJ_CORE_WARN(...)        ::Fejioa::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define FJ_CORE_INFO(...)        ::Fejioa::Log::GetCoreLogger()->info(__VA_ARGS__)
#define FJ_CORE_TRACE(...)       ::Fejioa::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define FJ_CORE_FATAL(...)       ::Fejioa::Log::GetCoreLogger()->fatal(__VA_ARGS__)

// Client log macros
#define FJ_ERROR(...)            ::Fejioa::Log::GetClientLogger()->error(__VA_ARGS__)
#define FJ_WARN(...)             ::Fejioa::Log::GetClientLogger()->warn(__VA_ARGS__)
#define FJ_INFO(...)             ::Fejioa::Log::GetClientLogger()->info(__VA_ARGS__)
#define FJ_TRACE(...)            ::Fejioa::Log::GetClientLogger()->trace(__VA_ARGS__)
#define FJ_FATAL(...)            ::Fejioa::Log::GetClientLogger()->fatal(__VA_ARGS__)