#pragma once

#include <iostream>
#include <unordered_map>
#include <BLog/colors.hpp>

#define BLogSetLogLevel(level) BLog::Logger::instance().setLogLevel(level)

#define BLogFileLine BLog::Logger::instance().setFileLine(__FILE__,__LINE__)

#define BLog(level, data) BLogFileLine << level << data << BLog::Special::flush
#define BLogLine(level, data) BLogFileLine << level << data << BLog::Special::endl

#define BLogDebug(data) BLog(BLog::Level::Debug, data)
#define BLogInfo(data) BLog(BLog::Level::Info, data)
#define BLogWarning(data) BLog(BLog::Level::Warning, data)
#define BLogError(data) BLog(BLog::Level::Error, data)
#define BLogFatal(data) BLog(BLog::Level::Fatal, data)

#define BLogDebugLine(data) BLogLine(BLog::Level::Debug, data)
#define BLogInfoLine(data) BLogLine(BLog::Level::Info, data)
#define BLogWarningLine(data) BLogLine(BLog::Level::Warning, data)
#define BLogErrorLine(data) BLogLine(BLog::Level::Error, data)
#define BLogFatalLine(data) BLogLine(BLog::Level::Fatal, data)

namespace BLog {
    enum class Level {
        Debug,
        Info,
        Warning,
        Error,
        Fatal
    };
    enum class Special {
        endl,
        flush
    };
    class Logger {
    public:
        Logger(const Logger&) = delete;
        Logger& operator=(const Logger&) = delete;

        static Logger& instance()
        {
            static Logger logger(std::cout);
            return logger;
        }
        Logger& operator<<(Level level);
        Logger& operator<<(Special special);
        Logger& operator<<(FGColor fgColor);
        Logger& operator<<(BGColor bgColor);
        template<typename T>
        Logger& operator<<(const T& t)
        {
            if (!m_levelSet)
            {
                this->operator<<(Level::Info);
            }
            if(m_level < m_logLevel)
            {
                return *this;
            }
            m_stream << t;
            return *this;
        }
        void setLogLevel(Level logLevel)
        {
            m_logLevel = logLevel;
        }
        Logger& setFileLine(const char* file, int line)
        {
            this->file = file;
            this->line = line;
            return *this;
        }
    private:
        Logger(std::ostream& stream, Level logLevel = Level::Debug);
        ~Logger() {};
        std::ostream& m_stream;
        Level m_level;
        Level m_logLevel;
        bool m_levelSet;
        const char* file;
        int line;
        std::unordered_map<Level, FGColor> m_fgColors;
        std::unordered_map<Level, BGColor> m_bgColors;
        std::unordered_map<Level, FGColor> m_tagFGColors;
        std::unordered_map<Level, BGColor> m_tagBGColors;
        std::unordered_map<Level, std::string> m_tags;
    };
}