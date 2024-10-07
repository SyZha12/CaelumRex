#ifndef APPLICATION_H
#define APPLICATION_H

// This is the main starting class of the engine
// This class must be exported (visible) for the external project to inherit and use its functionalities

#include "CRPrecompiled.h"
#include "Core/Log.h"
#include "Core/Window.h"
#include "Events/ApplicationEvent.h"
#include "Core/LayerStack.h"

namespace CaelumRex
{
    class CAELUMREX_EXPORT Application
    {
    public:
        Application();
        virtual ~Application();

        void Run();

        // Used for window events
        void OnEvent(Event& e);

        // Layers
        void PushLayer(Layer* layer);
        void PushOverlay(Layer* layer);

        static Application& Get() { return *s_Instance; }
        Window& GetWindow() { return *m_Window; }
    private:
        bool OnWindowClose(WindowCloseEvent& e);

        std::unique_ptr<Window> m_Window;
        bool m_Running = true;
        LayerStack m_LayerStack;

        static Application* s_Instance;
    };

    Application* CreateApplication();
}

#endif //APPLICATION_H
