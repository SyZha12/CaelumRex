#ifndef APPLICATION_H
#define APPLICATION_H

// This is the main starting class of the engine
// This class must be exported (visible) for the external project to inherit and use its functionalities

#include "CRPrecompiled.h"

#include "Core/Window.h"
#include "Core/LayerStack.h"
#include "Events/Event.h"
#include "Events/ApplicationEvent.h"    // For window closed event (for now)
#include "ImGui/ImGuiLayer.h"
#include "OpenGL/OpenGLContext.h"
// #include "Core/Input.h"
// #include "glm/glm.hpp"

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
        ImGuiLayer* m_ImGuiLayer;
        bool m_Running = true;
        LayerStack m_LayerStack;

        static Application* s_Instance;

    };

    // Called in Sandbox/Application
    extern Application* CreateApplication();
}

#endif //APPLICATION_H
