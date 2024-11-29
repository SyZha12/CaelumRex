/* CaelumRex Libraries */
#include <Core/Application.h>
#include <Renderer/Renderer.h>
#include <Debug/Instrumentor.h>

/* Third-Party Libraries & Co*/
#include <GLFW/glfw3.h>

namespace CaelumRex
{
    Application* Application::s_Instance = nullptr;

    Application::Application()
    {
        CR_PROFILE_FUNCTION();

        // Creates an Application pointer
        CR_CORE_INFO("Start CaelumRex Core Application...");
        if(s_Instance != nullptr)
            CR_CORE_ERROR("Application already exists");
        else
            s_Instance = this;

        {
            CR_PROFILE_SCOPE("Application - Window Create");
            // Create render window
            m_Window = Window::Create();
            m_Window->SetEventCallBack(BIND_EVENTS(OnEvent));
        }

        {
            CR_PROFILE_SCOPE("Application - Renderer Init");
            // Initialize rendering properties
            Renderer::Init();
        }

        {
            CR_PROFILE_SCOPE("Application - ImGui Layer Init");
            // Initialize ImGui context (initial properties) and attach new layer
            m_ImGuiLayer = new ImGuiLayer();
            PushOverlay(m_ImGuiLayer);
        }
    }

    void Application::Run()
    {
        while(m_Running)
        {
            CR_PROFILE_FUNCTION();

            // TODO This is for consistent frames; move to another class
            auto const time = static_cast<float>(glfwGetTime());
            Timestep const timestep = time - m_LastFrameTime;
            m_LastFrameTime = time;

            // Updates every layer (core window layer as well)
            if(!m_Minimized)
            {
                {
                    CR_PROFILE_SCOPE("Application - Minimized Layer");

                    for(Layer* layer : m_LayerStack)
                        layer->OnUpdate(timestep);
                }
            }

            // Updates every ImGui layer
            m_ImGuiLayer->Begin();
            for(Layer* layer : m_LayerStack)
                layer->OnImGuiRender();
            m_ImGuiLayer->End();

            // Updates and swaps window buffers
            m_Window->OnUpdate();
        }
    }

    void Application::OnEvent(Event& e)
    {
        CR_PROFILE_FUNCTION();

        // EventDispatcher is used to determine when certain events occur like WindowCloseEvent
        EventDispatcher dispatcher(e);
        dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENTS_DISPATCH(OnWindowClose));
        dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENTS_DISPATCH(OnWindowResize));
        dispatcher.Dispatch<WindowMinimizedEvent>(BIND_EVENTS_DISPATCH(OnWindowMinimized));

        // Call back each event that occurs on a layer
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

    bool Application::OnWindowResize(const WindowResizeEvent& e)
    {
        Renderer::OnWindowResize(e.GetWidth(), e.GetHeight());

        return false;
    }

    bool Application::OnWindowMinimized(const WindowMinimizedEvent& e)
    {
        if(e.IsMinimized())
        {
            m_Minimized = true;
            return true;
        }
        m_Minimized = false;

        return false;
    }

}
