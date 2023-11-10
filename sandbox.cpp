#include <BLog/blog.hpp>
#include <chrono>


int main()
{
    BLogSetLogLevel(BLog::Level::Debug);
    auto pre = std::chrono::system_clock::now();
    for(int i =0 ; i< 100000; i++)
    {
        BLog::Logger::instance() << BLog::Level::Debug << "Hello, World!" << BLog::Special::endl;
    }
    auto post = std::chrono::system_clock::now();
    auto deltams = std::chrono::duration_cast<std::chrono::milliseconds>(post - pre).count();
    BLogInfoLine("100000 logs took " << deltams << "ms");
    BLogInfoLine((double)deltams/100000.0f << "ms per log");


    BLogSetLogLevel(BLog::Level::Info);
    pre = std::chrono::system_clock::now();
    for(int i =0 ; i< 10000000; i++)
    {
        BLog::Logger::instance() << BLog::Level::Debug << "Hello, World!" << BLog::Special::endl;
    }
    post = std::chrono::system_clock::now();
    deltams = std::chrono::duration_cast<std::chrono::milliseconds>(post - pre).count();
    BLogInfoLine("10000000 invisible logs took " << deltams << "ms");
    BLogInfoLine((double)deltams/10000000.0f << "ms per log");

    BLogSetLogLevel(BLog::Level::Debug);
    BLog::Logger::instance() << BLog::Level::Debug << "Debug" << BLog::Special::endl;
    BLog::Logger::instance() << BLog::Level::Info << "Info" << BLog::Special::endl;
    BLog::Logger::instance() << BLog::Level::Warning << "Warning" << BLog::Special::endl;
    BLog::Logger::instance() << BLog::Level::Error << "Error" << BLog::Special::endl;
    BLog::Logger::instance() << BLog::Level::Fatal << "Fatal" << BLog::Special::endl;
}