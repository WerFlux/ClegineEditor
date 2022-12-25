#ifndef CLEGINE_CORE_LOGGER_HPP
#define CLEGINE_CORE_LOGGER_HPP

#include <EntryPoint.hpp>

#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>

namespace Clegine {
	class Logger {
	public:
		static void Init();
		inline static std::shared_ptr<spdlog::logger>& getLoggerData() {
			return loggerDataPtr;
		};
	private:
		static std::shared_ptr<spdlog::logger> loggerDataPtr;
	};
}

#define LOG_TRACE(...)			Clegine::Logger::getLoggerData()->trace(__VA_ARGS__)
#define LOG_DEBUG(...)			Clegine::Logger::getLoggerData()->debug(__VA_ARGS__)
#define LOG_INFO(...)			Clegine::Logger::getLoggerData()->info(__VA_ARGS__)
#define LOG_WARNING(...)		Clegine::Logger::getLoggerData()->warn(__VA_ARGS__)
#define LOG_ERROR(...)			Clegine::Logger::getLoggerData()->error(__VA_ARGS__)
#define LOG_CRITICAL(...)		Clegine::Logger::getLoggerData()->critical(__VA_ARGS__)

#endif // CLEGINE_CORE_LOGGER_HPP