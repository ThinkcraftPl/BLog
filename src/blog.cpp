#include <BLog/blog.hpp>
#include <chrono>
#include <date/date.h>

namespace BLog {
    Logger::Logger(std::ostream& stream, Level logLevel)
        : m_stream(stream)
        , m_level(Level::Debug)
        , m_levelSet(false)
        , m_fgColors({
            {Level::Debug, FGBrightBlack},
            {Level::Info, FGBrightWhite},
            {Level::Warning, FGBrightYellow},
            {Level::Error, FGBrightRed},
            {Level::Fatal, FGRed}
        })
        , m_bgColors({
            {Level::Debug, BGDefault},
            {Level::Info, BGDefault},
            {Level::Warning, BGDefault},
            {Level::Error, BGDefault},
            {Level::Fatal, BGDefault}
        })
        , m_tagFGColors({
            {Level::Debug, FGDefault},
            {Level::Info, FGDefault},
            {Level::Warning, FGDefault},
            {Level::Error, FGDefault},
            {Level::Fatal, FGDefault}
        }) 
        , m_tagBGColors({
            {Level::Debug, BGBrightBlack},
            {Level::Info, BGBrightWhite},
            {Level::Warning, BGYellow},
            {Level::Error, BGBrightRed},
            {Level::Fatal, BGRed}
        })
        , m_tags({
            {Level::Debug, "DBG"},
            {Level::Info, "INF"},
            {Level::Warning, "WAR"},
            {Level::Error, "ERR"},
            {Level::Fatal, "FTL"}
        })
        , m_logLevel(logLevel)
    {
        std::ios_base::sync_with_stdio(false);
        std::cout.tie(nullptr);
    }

    Logger& Logger::operator<<(Level level)
    {
        if(m_levelSet)
        {
            return *this;
        }
        m_level = level;
        m_levelSet = true;
        if(m_level < m_logLevel)
        {
            return *this;
        }
        m_stream << "\033[" << static_cast<int>(m_tagFGColors[m_level]) << ";" << static_cast<int>(m_tagBGColors[m_level]) << "m" << "[" << m_tags[m_level];
        auto now = std::chrono::system_clock::now();
        m_stream << date::format(" %T ", date::floor<std::chrono::milliseconds>(now));
        if(file != "")
            m_stream << file << ":" << line << "]";
        m_stream << "\033[" << static_cast<int>(m_fgColors[m_level]) << ";" << static_cast<int>(m_bgColors[m_level]) << "m ";

        return *this;
    }

    Logger& Logger::operator<<(Special special)
    {
        if(!m_levelSet)
        {
            return *this;
        }
        if(m_level < m_logLevel)
        {
            file="";
            line=0;
            m_levelSet = false;
            return *this;
        }
        switch (special)
        {
            case Special::endl:
                m_stream << "\033[0m" << std::endl;
                file="";
                line=0;
                m_levelSet = false;
                break;
            case Special::flush:
                m_stream << "\033[0m" << std::flush;
                file="";
                line=0;
                m_levelSet = false;
                break;
        }
        return *this;
    }

    Logger& Logger::operator<<(FGColor fgColor)
    {
        if(!m_levelSet || m_level < m_logLevel)
        {
            return *this;
        }
        m_stream << "\033[" << static_cast<int>(fgColor) << "m";
        return *this;
    }

    Logger& Logger::operator<<(BGColor bgColor)
    {
        if(!m_levelSet || m_level < m_logLevel)
        {
            return *this;
        }
        m_stream << "\033[" << static_cast<int>(bgColor) << "m";
        return *this;
    }
}