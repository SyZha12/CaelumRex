/* CaelumRex Libraries */
#include <Core/Window.h>
#include <Core/PlatformDetection.h>
#include <Core/Core.h>
#include <Linux/LinuxWindow.h>

namespace CaelumRex
{
    Scope<Window> Window::Create(const WindowProperties& props)
    {
        #ifdef CR_PLATFORM_LINUX
                return CreateScope<LinuxWindow>(props);
        #else
                CR_CORE_ERROR("Unknown platform");
                return nullptr;
        #endif
    }

}
