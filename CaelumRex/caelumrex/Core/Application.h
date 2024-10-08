#ifndef APPLICATION_H
#define APPLICATION_H

// This is the main starting class of the engine
// This class must be exported (visible) for the external project to inherit and use its functionalities

#include "CRPrecompiled.h"
#include "Core/Log.h"
// Used to send window object
#include "Core/Window.h"
// For window closed event (for now)
#include "Events/ApplicationEvent.h"
#include "Core/LayerStack.h"
#include "Linux/LinuxWindow.h"

namespace CaelumRex
{
    class CAELUMREX_EXPORT Application
    {
    public:
        Application();
        virtual ~Application();

        // Main game loop
        void Run();

        // Used for window events
        // This way Application isn't directly linked to the Window class
        void OnEvent(Event& e);

        // Layers
        void PushLayer(Layer* layer);
        void PushOverlay(Layer* layer);

        Window& GetWindow() const { return *m_Window; }

        // Returns the instance of the application for another class to execute its functions
        static Application& Get() { return *s_Instance; }

    private:
        bool OnWindowClose(WindowCloseEvent& e);

        std::unique_ptr<Window> m_Window;
        bool m_Running = true;
        LayerStack m_LayerStack;

        // TODO s_Instance is infinite loop
        static Application* s_Instance;

    };

    Application* CreateApplication();
}

#endif //APPLICATION_H
