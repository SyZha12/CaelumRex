#include "Sandbox2D.h"

#define GLM_ENABLE_EXPERIMENTAL
#include "glm/gtx/transform.hpp"

Sandbox2D::Sandbox2D()
    : Layer("Sandbox2D"), m_CameraController(1920 / 1080)
{
}

void Sandbox2D::OnAttach()
{
    m_2DVertexArray = CaelumRex::VertexArray::Create();

    float vertices[] = {
        -0.5f,  0.5f, 0.0f,
         0.5f,  0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f
    };
    CaelumRex::Ref<CaelumRex::VertexBuffer> m_2DVertexBuffer = CaelumRex::VertexBuffer::Create(vertices, sizeof(vertices));
    m_2DVertexBuffer->SetLayout({
        { CaelumRex::ShaderDataType::Float3, "v_Position" }
    });
    m_2DVertexArray->AddVertexBuffer(m_2DVertexBuffer);

    uint32_t indices[] = { 0, 1, 2, 1, 2, 3 };
    CaelumRex::Ref<CaelumRex::IndexBuffer> m_2DIndexBuffer = CaelumRex::IndexBuffer::Create(indices, sizeof(indices));
    m_2DVertexArray->SetIndexBuffer(m_2DIndexBuffer);

    m_ShaderLibrary.Load("assets/shaders/BasicShader.glsl");
}

void Sandbox2D::OnDetach()
{

}

void Sandbox2D::OnUpdate(CaelumRex::Timestep ts)
{
    m_CameraController.OnUpdate(ts);

    CaelumRex::Renderer::Begin(m_CameraController.GetCamera());
    auto shader = m_ShaderLibrary.Get("BasicShader");
    CaelumRex::Renderer::Dispatch(shader, m_2DVertexArray, glm::scale(glm::mat4(1.0f), glm::vec3(0.5f)));
    CaelumRex::Renderer::End();

}

void Sandbox2D::OnImGuiRender()
{

}

void Sandbox2D::OnEvent(CaelumRex::Event& event)
{
    m_CameraController.OnEvent(event);
}
