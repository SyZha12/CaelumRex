#include "Core/Application.h"

namespace CaelumRex
{
#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)
    Application::Application()
    {
        // Create a window
        m_Window = std::unique_ptr<Window>(Window::Create());
        m_Window->SetEventCallBack(BIND_EVENT_FN(OnEvent));
    }

    Application::~Application()
    {

    }

    void Application::OnEvent(Event& e)
    {
        // EventDispatcher is used to determine when certain events occur like WindowCloseEvent
        EventDispatcher dispatcher(e);
        dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));

        CR_CORE_TRACE("{0}", e);
    }

    void Application::Run()
    {
        while(m_Running)
        {
            glClearColor(1.0f, 0.0f, 1.0f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            m_Window->OnUpdate();
        }
    }

    bool Application::OnWindowClose(WindowCloseEvent& e)
    {
        m_Running = false;
        return true;
    }


    Application* CreateApplication();
}