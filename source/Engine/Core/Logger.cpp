#include "Logger.h"
#include "FileIO.h"
#include <iostream>

namespace antares {
	bool Logger::Log(LogLevel logLevel, const std::string& filename, int lineNumber) {
		if (logLevel < m_logLevel) return false;
		switch (logLevel) {
		case LogLevel::Info:
			*this << "INFO: ";
			break;
		case LogLevel::Warning:
			*this << "WARNING: ";
			break;
		case LogLevel::Error:
			*this << "ERROR: ";
			break;
		case LogLevel::Assert:
			*this << "ASSERT: ";
			break;
		default:
			break;
		}

		*this << getFileName(filename) << "(" << lineNumber << ") - ";

		return true;
	}

	Logger g_logger(LogLevel::Info, &std::cout, "Log.txt");
}