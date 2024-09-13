#include "ColorPCH.h"
#include "Log.h"

#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>

namespace Color::Log
{
	std::shared_ptr<spdlog::logger> g_CoreLogger, g_ClientLogger, g_AssertLogger;

	void Init()
	{
		spdlog::sink_ptr sinks[] =
		{
			std::make_shared<spdlog::sinks::stdout_color_sink_mt>(),
			std::make_shared<spdlog::sinks::basic_file_sink_mt>("Color.log", true)
		};

		sinks[0]->set_pattern("%^[%T] %n: %v%$");
		sinks[1]->set_pattern("[%T] (%l) %n: %v");

		auto CreateLogger = [sinks](const std::string& name) -> std::shared_ptr<spdlog::logger>
		{
			std::shared_ptr<spdlog::logger> logger = std::make_shared<spdlog::logger>(name, begin(sinks), end(sinks));
			spdlog::register_logger(logger);

			logger->set_level(spdlog::level::trace);
			logger->flush_on(spdlog::level::trace);

			return logger;
		};

		g_CoreLogger = CreateLogger("ENGINE");
		g_ClientLogger = CreateLogger("CLIENT");
		g_AssertLogger = CreateLogger("ASSERT");
	}
}
