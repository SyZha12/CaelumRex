#ifndef APPLICATION_H
#define APPLICATION_H

#include "CRPrecompiled.h"

#include "Events/ApplicationEvent.h"
#include "Core/Log.h"
#include "Core/Window.h"

namespace CaelumRex
{
    class CAELUMREX_EXPORT Application
    {
    public:
        Application();
        virtual ~Application();

        void Run();
    private:
        std::unique_ptr<Window> m_Window;
        bool m_Running = true;
    };

    Application* CreateApplication();
}

#endif //APPLICATION_H
