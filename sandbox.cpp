#include <BLog/blog.hpp>
#include <chrono>
#include <thread>

int main()
{
    BLogInstanceName("Sandbox main");
    //*/
    BLogSetLogLevel(BLog::Level::Debug);
    auto pre = std::chrono::system_clock::now();
    static int test_lines = 10000;
    for(int i =0 ; i< test_lines; i++)
    {
        BLogDebugLine("Hello, World!");
    }
    auto post = std::chrono::system_clock::now();
    auto deltams = std::chrono::duration_cast<std::chrono::milliseconds>(post - pre).count();
    BLogInfoLine(test_lines<<" logs took " << deltams << "ms");
    BLogInfoLine((double)deltams/test_lines << "ms per log");


    BLogSetLogLevel(BLog::Level::Info);
    pre = std::chrono::system_clock::now();
    for(int i =0 ; i< 10000000; i++)
    {
        BLogDebugLine("Hello, World!");
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
    std::cout<<std::flush;
    //*/
    auto lambda = [](std::string name){
        BLogInstanceName(name);
        for(int i =0 ; i< 5; i++)
        {
            BLogDebugLine("Hello, thread "<<std::this_thread::get_id()<<"!");
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    };
    auto thread1 = std::thread(lambda, "Thread 1");
    auto thread2 = std::thread(lambda, "Thread 2");

    thread1.join();
    thread2.join();
    //*/
}