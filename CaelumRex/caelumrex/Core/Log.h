#ifndef LOG_H
#define LOG_H

/**
 *  @author Symen Zhang
 *  @brief This class uses spdlog and is very fast and header-only (compiled is also possible). Spdlog uses the
 *         feature-rich formatting of the fmt library.
 */

/** Third-Party Libraries & Co **/
#include <spdlog/spdlog.h>

namespace CaelumRex
{
    class Log
    {
    public:
        static void Init();

        static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
        static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
    private:
        static std::shared_ptr<spdlog::logger> s_CoreLogger;
        static std::shared_ptr<spdlog::logger> s_ClientLogger;
    };
}

// LOG MACROS
#define CR_CORE_TRACE(...)  ::CaelumRex::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define CR_CORE_INFO(...)   ::CaelumRex::Log::GetCoreLogger()->info(__VA_ARGS__)
#define CR_CORE_WARN(...)   ::CaelumRex::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define CR_CORE_ERROR(...)  ::CaelumRex::Log::GetCoreLogger()->error(__VA_ARGS__)
#define CR_CORE_FATAL(...)  ::CaelumRex::Log::GetCoreLogger()->fatal(__VA_ARGS__)

#define CR_TRACE(...)       ::CaelumRex::Log::GetClientLogger()->trace(__VA_ARGS__)
#define CR_INFO(...)        ::CaelumRex::Log::GetClientLogger()->info(__VA_ARGS__)
#define CR_WARN(...)        ::CaelumRex::Log::GetClientLogger()->warn(__VA_ARGS__)
#define CR_ERROR(...)       ::CaelumRex::Log::GetClientLogger()->error(__VA_ARGS__)
#define CR_FATAL(...)       ::CaelumRex::Log::GetClientLogger()->fatal(__VA_ARGS__)

#endif //LOG_H
