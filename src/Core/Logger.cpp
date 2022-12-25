#include <Core/Logger.hpp>

namespace Clegine {
	std::shared_ptr<spdlog::logger> Logger::loggerDataPtr;

	void Logger::Init() {
		std::vector<spdlog::sink_ptr> logSinksPtr;
		logSinksPtr.emplace_back(std::make_shared<spdlog::sinks::stdout_color_sink_mt>());
		logSinksPtr.emplace_back(std::make_shared<spdlog::sinks::basic_file_sink_mt>("ClegineEditor.log", true));

		logSinksPtr[0]->set_pattern("%^[%T] %n: %v%$");
		logSinksPtr[1]->set_pattern("[%T] [%l] %n: %v");

		loggerDataPtr = std::make_shared<spdlog::logger>("Clegine", std::begin(logSinksPtr), std::end(logSinksPtr));
		loggerDataPtr->set_level(spdlog::level::trace);
		loggerDataPtr->flush_on(spdlog::level::trace);

		spdlog::register_logger(loggerDataPtr);
	}
}