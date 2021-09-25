#pragma once

#include <string>
#include <fstream>
#include <algorithm>
#include <chrono>
#include <thread>
#include <mutex>
#include <iomanip>

namespace Feijoa
{
	using FloatingPointMicroseconds = std::chrono::duration<double, std::micro>;

	struct ProfileResult
	{
		std::string Name;
		FloatingPointMicroseconds Start;
		std::chrono::microseconds ElapsedTime;
		std::thread::id ThreadID;
	};

	struct InstrumentationSession
	{
		std::string Name;
	};

	class Instrumentor
	{
	public:
		Instrumentor()
			: m_CurrentSession(nullptr)
		{
		}

		void BeginSession(const std::string& name, const std::string& filepath = "results.json")
		{
			std::lock_guard lock(m_Mutex);
			if (m_CurrentSession)
			{
				if (Log::GetCoreLogger()) // Edge case: BeginSession might be before Log::Init()
					FJ_CORE_ERROR("Instrumention::BeginSession('{0}') when session '{1}' already open.", name, m_CurrentSession->Name);

				InternalEndSession();
			}

			m_OutputStream.open(filepath);
			if (m_OutputStream.is_open())
			{
				m_CurrentSession = new InstrumentationSession{ name };
				WriteHeader();
			}
			else
				if (Log::GetCoreLogger()) // Edge case: BeginSession might be before Log::Init()
					FJ_CORE_ERROR("Instrumentor could not open results file '{0}'.", filepath);
		}

		void EndSession()
		{
			std::lock_guard lock(m_Mutex);
			InternalEndSession();
		}

		void WriteProfile(const ProfileResult& result)
		{
			std::stringstream json;

			json << std::setprecision(3) << std::fixed;
			json << ",{";
			json << "\"cat\":\"function\",";
			json << "\"dur\":" << (result.ElapsedTime.count()) << ",";
			json << "\"name\":\"" << result.Name << "\",";
			json << "\"ph\":\"X\",";
			json << "\"pid\":0,";
			json << "\"tid\":" << result.ThreadID << ",";
			json << "\"ts\":" << result.Start.count();
			json << "}";

			std::lock_guard lock(m_Mutex);
			if (m_CurrentSession)
			{
				m_OutputStream << json.str();
				m_OutputStream.flush();
			}
		}

		static Instrumentor& Get()
		{
			static Instrumentor instance;
			return instance;
		}

	private:
		void WriteHeader()
		{
			m_OutputStream << "{\"otherData\": {}, \"traceEvents\":[{}";
			m_OutputStream.flush();
		}

		void WriteFooter()
		{
			m_OutputStream << "]}";
			m_OutputStream.flush();
		}

		// Note: you must already own lock on m_Mutex before calling InternalEndSession
		void InternalEndSession()
		{
			if (m_CurrentSession)
			{
				WriteFooter();
				m_OutputStream.close();
				delete m_CurrentSession;
				m_CurrentSession = nullptr;
			}
		}

	private:
		InstrumentationSession* m_CurrentSession;
		std::ofstream m_OutputStream;
		std::mutex m_Mutex;
	};

	class InstrumentationTimer
	{
	public:
		InstrumentationTimer(const char* name)
			: m_Name(name), m_Stopped(false)
		{
			m_StartTimePoint = std::chrono::steady_clock::now();
		}

		~InstrumentationTimer()
		{
			if (!m_Stopped)
				Stop();
		}

		void Stop()
		{
			auto endTimePoint = std::chrono::steady_clock::now();
			auto highResStart = FloatingPointMicroseconds{ m_StartTimePoint.time_since_epoch() };
			auto elapsedTime = std::chrono::time_point_cast<std::chrono::microseconds>(endTimePoint).time_since_epoch() - std::chrono::time_point_cast<std::chrono::microseconds>(m_StartTimePoint).time_since_epoch();

			Instrumentor::Get().WriteProfile({ m_Name, highResStart, elapsedTime, std::this_thread::get_id() });

			m_Stopped = true;
		}

	private:
		const char* m_Name;
		bool m_Stopped;
		std::chrono::time_point<std::chrono::steady_clock> m_StartTimePoint;
	};

	namespace InstrumentorUtils
	{
		template <size_t N>
		struct ChangeResult
		{
			char Data[N];
		};

		template <size_t N, size_t K>
		constexpr auto CleanupOutputString(const char(&expr)[N], const char(&remove)[K])
		{
			ChangeResult<N> result = {};

			size_t srcIndex = 0;
			size_t dstIndex = 0;
			while (srcIndex < N)
			{
				size_t matchIndex = 0;
				while (matchIndex < K - 1 && srcIndex + matchIndex < N - 1 && expr[srcIndex + matchIndex] == remove[matchIndex])
					matchIndex++;

				if (matchIndex == K - 1)
					srcIndex += matchIndex;

				result.Data[dstIndex++] = expr[srcIndex] == '"' ? '\'' : expr[srcIndex];
				srcIndex++;
			}
			return result;
		}
	}

#define FJ_PROFILE 0
#if FJ_PROFILE
	#if defined(__GNUC__) || (defined(__MWERKS__) && (__MWERKS__ >= 0x3000)) || (defined(__ICC) && (__ICC >= 0x600)) || defined(__ghs__)
		#define FJ_FUNC_SIG __PRETTY_FUNCTION__
	#elif defined(__DMC__) && (__DMC >= 0x810)
		#define FJ_FUNC_SIG __PRETTY_FUNCTION__
	#elif (defined(__FUNCSIG__)) || (_MSC_VER)
		#define FJ_FUNC_SIG __FUNCSIG__
	#elif (defined(__INTEL_COMPILER) && (__INTEL_COMPILER >= 600)) || (defined(__IBMCPP__) && (__IBMCPP_ >= 500)
		#define FJ_FUNC_SIG __FUNCTION__
	#elif (defined(__BORLANDC__) && __BORLANDC__ >= 0x550)
		#define FJ_FUNC_SIG __FUNC__
	#elif defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199901)
		#define __func__
	#elif defined(__cplusplus) && (__cplusplus >= 201103)
		#define __func__
	#else
		#define FJ_FUNC_SIG "FJ_FUNC_SIG unknown!"
	#endif

	#define FJ_PROFILE_BEGIN_SESSION(name, filepath) ::Feijoa::Instrumentor::Get().BeginSession(name, filepath)
	#define FJ_PROFILE_END_SESSION() ::Feijoa::Instrumentor::Get().EndSession()
	#define FJ_PROFILE_SCOPE(name) constexpr auto fixedName = ::Feijoa::InstrumentorUtils::CleanupOutputString(name, "__cdecl ");\
									::Feijoa::InstrumentationTimer timer##__LINE__(fixedName.Data);
	#define FJ_PROFILE_FUNCTION() FJ_PROFILE_SCOPE(FJ_FUNC_SIG)
#else
	#define FJ_PROFILE_BEGIN_SESSION(name, filepath)
	#define FJ_PROFILE_END_SESSION()
	#define FJ_PROFILE_SCOPE(name)
	#define FJ_PROFILE_FUNCTION()
#endif
}