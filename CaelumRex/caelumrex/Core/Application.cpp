#include "Core/Application.h"
#include <glad/glad.h>

namespace CaelumRex
{
#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

    // Static members need to be defined in the source file as well; this is for the application instance
    Application* Application::s_Instance = nullptr;

    static GLenum ShaderDataTypeToOpenGLBaseType(const ShaderDataType type)
    {
        switch(type)
        {
        case ShaderDataType::Float:         return GL_FLOAT;
        case ShaderDataType::Float2:        return GL_FLOAT;
        case ShaderDataType::Float3:        return GL_FLOAT;
        case ShaderDataType::Float4:        return GL_FLOAT;
        case ShaderDataType::Mat3:          return GL_FLOAT;
        case ShaderDataType::Mat4:          return GL_FLOAT;
        case ShaderDataType::Int:           return GL_INT;
        case ShaderDataType::Int2:          return GL_INT;
        case ShaderDataType::Int3:          return GL_INT;
        case ShaderDataType::Int4:          return GL_INT;
        case ShaderDataType::Bool:          return GL_BOOL;
        }

        CR_CORE_ASSERT(false, "Unknown ShaderDataType.");
        return 0;
    }

    Application::Application()
    {
        CR_CORE_INFO("Start CaelumRex Core Application...");
        {
            // Creates an Application pointer
            CR_CORE_ASSERT(!s_Instance, "Application already exists!")
            s_Instance = this;
        }


        // Create the primary window
        m_Window = std::unique_ptr<Window>(Window::Create());
        m_Window->SetEventCallBack(BIND_EVENT_FN(OnEvent));

        // Create the ImGui Layer
        m_ImGuiLayer = new ImGuiLayer();
        PushLayer(m_ImGuiLayer);

        m_VertexArray.reset(VertexArray::Create());

        float vertices[3 * 3] =
        {
            -0.5f, -0.5f, 0.0f,
            0.5f, -0.5f, 0.0f,
            0.0f, 0.5f, 0.0f
        };
        m_VertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));
        BufferLayout layout = {
            { ShaderDataType::Float3, "a_Position" }
        };

        uint32_t index = 0;
        for(const auto& element : layout)
        {
            glEnableVertexAttribArray(index);
            glVertexAttribPointer(
                index,
                element.GetComponentCount(),
                ShaderDataTypeToOpenGLBaseType(element.Type),
                element.Normalized ? GL_TRUE : GL_FALSE,
                layout.GetStride(),
                reinterpret_cast<const void*>(element.Offset)
            );
            index++;
        }

        uint32_t indices[3] = { 0, 1, 2 };
        m_IndexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));

        std::string vertexSrc = R"(
            #version 460 core

            layout(location = 0) in vec3 a_Position;

            void main()
            {
                gl_Position = vec4(a_Position, 1.0);
            }
        )";

        std::string fragmentSrc = R"(
            #version 460 core

            layout(location = 0) out vec4 color;

            void main()
            {
                color = vec4(0.5, 0.2, 1.0, 1.0);
            }
        )";

        m_Shader.reset(new Shader(vertexSrc, fragmentSrc));
    }

    Application::~Application()
    {
    }

    void Application::Run()
    {
        while(m_Running)
        {
            // glClearColor(1.0f, 0.0f, 1.0f, 1.0f);
            // glClear(GL_COLOR_BUFFER_BIT);

            m_Shader->Bind();
            m_VertexArray->Bind();
            glDrawElements(GL_TRIANGLES, m_IndexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr);
            m_VertexArray->Unbind();

            for(Layer* layer : m_LayerStack)
                layer->OnUpdate();

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


    // Application* CreateApplication();
}
