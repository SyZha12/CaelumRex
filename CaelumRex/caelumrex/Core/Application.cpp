#include "Core/Application.h"

namespace CaelumRex
{
#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

    // Static members need to be defined in the source file as well; this is for the application instance
    Application* Application::s_Instance = nullptr;


    Application::Application()
    {
        // Creates an Application pointer
        CR_CORE_ASSERT(!s_Instance, "Application already exists!")
        s_Instance = this;

        // Create a window
        m_Window = std::unique_ptr<Window>(Window::Create());
        m_Window->SetEventCallBack(BIND_EVENT_FN(OnEvent));
    }

    Application::~Application()
    {
    }

    void Application::Run()
    {
        while(m_Running)
        {
            glClearColor(1.0f, 0.0f, 1.0f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            for(Layer* layer : m_LayerStack)
                layer->OnUpdate();

            // auto[x, y] = Input::GetMousePosition();
            // CR_CORE_TRACE("{0}, {1}", x, y);

            m_Window->OnUpdate();
        }
    }

    void Application::OnEvent(Event& e)
    {
        // EventDispatcher is used to determine when certain events occur like WindowCloseEvent
        EventDispatcher dispatcher(e);
        dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));
        // CR_CORE_INFO("{0}", e.IsInCategory(EventCategoryApplication));
        // Use this to see events happening in the log
        // CR_CORE_TRACE("{0}", e);

        for(auto it = m_LayerStack.end(); it != m_LayerStack.begin();)
        {
            (*--it)->OnEvent(e);
            if(e.handled)
                break;
        }
    }

    void Application::PushLayer(Layer* layer)
    {
        m_LayerStack.PushLayer(layer);
        layer->OnAttach();
    }

    void Application::PushOverlay(Layer* layer)
    {
        m_LayerStack.PushOverlay(layer);
        layer->OnAttach();
    }

    bool Application::OnWindowClose(WindowCloseEvent& e)
    {
        m_Running = false;
        return true;
    }


    // Application* CreateApplication();
}