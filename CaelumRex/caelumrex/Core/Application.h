#ifndef APPLICATION_H
#define APPLICATION_H

/**
 * @author Symen Zhang
 * @brief Main application class of the engine. This class will be used for the external project to inherit, so the user
 *        will be able to apply its functionalities. For use; start by calling the external CreateApplication function.
 */

/** CaelumRex libraries **/
#include <caelumrex_export.h>
#include <Core/LayerStack.h>
#include <Core/Window.h>
#include <Events/ApplicationEvent.h>    // For window closed event (for now)

/** Third-Party Libraries & Co **/
#include <ImGui/ImGuiLayer.h>

namespace CaelumRex
{
    class CAELUMREX_EXPORT Application
    {
    public:
        Application();
        virtual ~Application() = default;

        void Run();
        void OnEvent(Event& e);

        void PushLayer(Layer* layer);
        void PushOverlay(Layer* layer);

        [[nodiscard("Return value not used")]]
        Window& GetWindow() const { return *m_Window; }

        [[nodiscard("Return value not used")]]
        static Application& Get() { return *s_Instance; }

    private:
        // TODO Move these functions outside of Application
        bool OnWindowClose(WindowCloseEvent& e);
        bool OnWindowResize(const WindowResizeEvent& e);
        bool OnWindowMinimized(const WindowMinimizedEvent& e);

        Scope<Window> m_Window;
        ImGuiLayer* m_ImGuiLayer;
        LayerStack m_LayerStack;

        bool m_Running = true;
        bool m_Minimized = false;
        float m_LastFrameTime = 0.0f;

        static Application* s_Instance;
    };

    extern Application* CreateApplication();
}

#endif //APPLICATION_H
