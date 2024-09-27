#pragma once

#include "Misc/Popup.h"

#define SPDLOG_LEVEL_NAMES { "trace", "__unused__", "info", "warn", "error", "fatal", "off" } 
#define SPDLOG_SHORT_LEVEL_NAMES { "T", "__UNUSED__", "I", "W", "E", "F", "O" } 

#define SPDLOG_FMT_EXTERNAL
#define FMT_DEPRECATED_OSTREAM
#define FMT_HEADER_ONLY

#pragma warning(push, 0) // Disable warnings coming from spdlog headers (all warnings disabled until they're popped)
	#include <spdlog/spdlog.h>
	#include <spdlog/fmt/ostr.h> // For user-types' operator<< formatting
#pragma warning(pop) // Re-enable warnings

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/string_cast.hpp>
#include <glm/glm.hpp>

namespace Color::Log
{
	extern std::shared_ptr<spdlog::logger> g_CoreLogger, g_ClientLogger, g_AssertLogger;
	void Init();

	template <typename... Args>
	static void RuntimeError(const std::string& loggerName, bool isFatal, std::string_view fmt, Args&&... args)
	{
		std::string msg = fmt::vformat(fmt, fmt::make_format_args(args...)) + "\n\nPropagator logger: " + loggerName;

		if (isFatal)
		{
			msg += "\nThe application will be aborted due to that.";
		}

		Scope<Popup> popup = Popup::Create(isFatal ? "Fatal error!" : "Runtime error!", msg, PopupButtonSet::Ok, PopupIcon::Error);
		popup->CreateAndWait();

		if (isFatal)
		{
			exit(1);
		}
	}
}

template <typename OStream, glm::length_t L, typename T, glm::qualifier Q>
inline OStream& operator<<(OStream& stream, const glm::vec<L, T, Q>& vector)
{
	return stream << glm::to_string(vector);
}

template <typename OStream, glm::length_t C, glm::length_t R, typename T, glm::qualifier Q>
inline OStream& operator<<(OStream& stream, const glm::mat<C, R, T, Q>& matrix)
{
	return stream << glm::to_string(matrix);
}

template <typename OStream, typename T, glm::qualifier Q>
inline OStream& operator<<(OStream& stream, const glm::qua<T, Q>& quat)
{
	return stream << glm::to_string(quat);
}

#ifdef CL_TEST_BUILD
	#define CL_LOGGER_TRACE(pLogger, ...)   pLogger->log(spdlog::level::trace,    __VA_ARGS__);
	#define CL_LOGGER_INFO(pLogger, ...)    pLogger->log(spdlog::level::info,     __VA_ARGS__);
	#define CL_LOGGER_WARN(pLogger, ...)    pLogger->log(spdlog::level::warn,     __VA_ARGS__);
	#define CL_LOGGER_ERROR(pLogger, ...)   pLogger->log(spdlog::level::err,      __VA_ARGS__);
	#define CL_LOGGER_FATAL(pLogger, ...) { pLogger->log(spdlog::level::critical, __VA_ARGS__); ::exit(1); }
#else
	#define CL_LOGGER_TRACE(pLogger, ...)
	#define CL_LOGGER_INFO(pLogger, ...)
	#define CL_LOGGER_WARN(pLogger, ...)
	#define CL_LOGGER_ERROR(pLogger, ...)   ::Color::Log::RuntimeError(pLogger->name(), false, __VA_ARGS__)
	#define CL_LOGGER_FATAL(pLogger, ...)   ::Color::Log::RuntimeError(pLogger->name(), true, __VA_ARGS__)
#endif

#define CL_CORE_TRACE(...)   CL_LOGGER_TRACE(::Color::Log::g_CoreLogger, __VA_ARGS__)
#define CL_CORE_INFO(...)    CL_LOGGER_INFO (::Color::Log::g_CoreLogger, __VA_ARGS__)
#define CL_CORE_WARN(...)    CL_LOGGER_WARN (::Color::Log::g_CoreLogger, __VA_ARGS__)
#define CL_CORE_ERROR(...)   CL_LOGGER_ERROR(::Color::Log::g_CoreLogger, __VA_ARGS__)
#define CL_CORE_FATAL(...)   CL_LOGGER_FATAL(::Color::Log::g_CoreLogger, __VA_ARGS__)

#define CL_TRACE(...)        CL_LOGGER_TRACE(::Color::Log::g_ClientLogger, __VA_ARGS__)
#define CL_INFO(...)         CL_LOGGER_INFO (::Color::Log::g_ClientLogger, __VA_ARGS__)
#define CL_WARN(...)         CL_LOGGER_WARN (::Color::Log::g_ClientLogger, __VA_ARGS__)
#define CL_ERROR(...)        CL_LOGGER_ERROR(::Color::Log::g_ClientLogger, __VA_ARGS__)
#define CL_FATAL(...)        CL_LOGGER_FATAL(::Color::Log::g_ClientLogger, __VA_ARGS__)

#define CL_ASSERT_TRACE(...) CL_LOGGER_TRACE(::Color::Log::g_AssertLogger, __VA_ARGS__)
#define CL_ASSERT_INFO(...)  CL_LOGGER_INFO (::Color::Log::g_AssertLogger, __VA_ARGS__)
#define CL_ASSERT_WARN(...)  CL_LOGGER_WARN (::Color::Log::g_AssertLogger, __VA_ARGS__)
#define CL_ASSERT_ERROR(...) CL_LOGGER_ERROR(::Color::Log::g_AssertLogger, __VA_ARGS__)
#define CL_ASSERT_FATAL(...) CL_LOGGER_FATAL(::Color::Log::g_AssertLogger, __VA_ARGS__)
