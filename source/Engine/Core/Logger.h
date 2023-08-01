#pragma once
#include <string>
#include <cassert>
#include <fstream>

#define INFO_LOG    { antares::g_logger.Log(antares::LogLevel::Info, __FILE__, __LINE__); }
#define WARNING_LOG { antares::g_logger.Log(antares::LogLevel::Warning, __FILE__, __LINE__); }
#define ERROR_LOG   { antares::g_logger.Log(antares::LogLevel::Error, __FILE__, __LINE__); }
#define ASSERT_LOG  { antares::g_logger.Log(antares::LogLevel::Assert, __FILE__, __LINE__); }

namespace antares {
	enum class LogLevel {
		Info,
		Warning,
		Error,
		Assert
	};
	class Logger {
	public:
		Logger(LogLevel logLevel, std::ostream* ostream) : 
			m_ostream{ ostream }, 
			m_logLevel{ logLevel } 
		{}

		bool Log(LogLevel logLevel, const std::string& filename, int lineNumber);
	private:
		LogLevel m_logLevel;
		std::ostream* m_ostream = nullptr;
		std::ofstream m_fstream;

	};
	
	extern Logger g_logger;
}