#ifndef Entry_H
#define Entry_H

/**
 *  @author Symen Zhang
 *  @brief Main entry point for the application; CreateApplication is called from the engine, so that initializing
 *         starts from here. The application doesn't start, if the platform detected is not supported.
 */

/* CaelumRex Libraries */
#include <Core/PlatformDetection.h>
#include <Debug/Instrumentor.h>

#ifdef CR_PLATFORM_LINUX
int main(int argc, char ** argv)
{
    // Initialise log of the core application
    CaelumRex::Log::Init();

    CR_PROFILE_BEGIN_SESSION("Start Application", "Sandbox/profiles/CaelumRex-StartApplication.json");
    auto* application = CaelumRex::CreateApplication();
    CR_PROFILE_END_SESSION();

    CR_PROFILE_BEGIN_SESSION("Runtime Application", "Sandbox/profiles/CaelumRex-RuntimeApplication.json");
    application->Run();
    CR_PROFILE_END_SESSION();

    CR_PROFILE_BEGIN_SESSION("Shutdown Application", "Sandbox/profiles/CaelumRex-ShutdownApplication.json");
    delete application;
    CR_PROFILE_END_SESSION();
}
#endif //CR_PLATFORM_LINUX

#endif //Entry_H
