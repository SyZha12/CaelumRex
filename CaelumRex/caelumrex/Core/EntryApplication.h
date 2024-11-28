#ifndef ENTRYAPPLICATION_H
#define ENTRYAPPLICATION_H

/**
 *  @author Symen Zhang
 *  @brief Main entry point for the application; CreateApplication is called from the engine, so that initializing the
 *         starts from here. The application doesn't start, if the platform detected is not supported.
 */

/** CaelumRex libraries **/
#include <Core/PlatformDetection.h>

#ifdef CR_PLATFORM_LINUX
int main(int argc, char ** argv)
{
    // Initialise log of the core application
    CaelumRex::Log::Init();

    auto* application = CaelumRex::CreateApplication();
    application->Run();
    delete application;
}
#endif //CR_PLATFORM_LINUX

#endif //ENTRYAPPLICATION_H
