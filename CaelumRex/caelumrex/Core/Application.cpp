#include "Core/Application.h"

#include "GLFW/glfw3.h"
#include "Renderer/Renderer.h"

namespace CaelumRex
{
#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

    // Static members need to be defined in the source file as well; this is for the application instance
    Application* Application::s_Instance = nullptr;

    Application::Application()
    {
        CR_CORE_INFO("Start CaelumRex Core Application...");
        {
            // Creates an Application pointer
            if(s_Instance != NULL)
                CR_CORE_ERROR("Application already exists! {0}");
            else
                s_Instance = this;
        }

        // Create the primary window
        m_Window = std::unique_ptr<Window>(Window::Create());
        m_Window->SetEventCallBack(BIND_EVENT_FN(OnEvent));

        // Create the ImGui Layer
        m_ImGuiLayer = new ImGuiLayer();
        PushLayer(m_ImGuiLayer);
    }

    Application::~Application()
    {
    }

    void Application::Run()
    {
        while(m_Running)
        {
            float time = static_cast<float>(glfwGetTime());
            Timestep timestep = time - m_LastFrameTime;
            m_LastFrameTime = time;

            for(Layer* layer : m_LayerStack)
                layer->OnUpdate(timestep);

            m_ImGuiLayer->Begin();
            for(Layer* layer : m_LayerStack)
                layer->OnImGuiRender();
            m_ImGuiLayer->End();

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
            if(e.m_Handled)
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

}
