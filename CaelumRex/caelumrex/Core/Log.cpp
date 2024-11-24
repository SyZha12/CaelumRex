#include "Core/Log.h"

namespace CaelumRex
{
    std::shared_ptr<spdlog::logger> Log::s_CoreLogger;
    std::shared_ptr<spdlog::logger> Log::s_ClientLogger;

    void Log::Init()
    {
        spdlog::set_pattern("%^[%T] %-10l[%n]: %v%$");
        // Create and return a shared_ptr to a multithreaded console logger
        // std::cout << spdlog::get("CaelumRex") << std::endl;   : returns the shared_ptr and shows the address
        s_CoreLogger = spdlog::stdout_color_mt("CaelumRex");
        s_CoreLogger->set_level(spdlog::level::trace);
        s_ClientLogger = spdlog::stdout_color_mt("Application");
        s_ClientLogger->set_level(spdlog::level::trace);
    }

}