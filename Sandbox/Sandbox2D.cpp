#include "Sandbox2D.h"

Sandbox2D::Sandbox2D()
    : Layer("Sandbox2D"), m_CameraController(1920 / 1080)
{
}

void Sandbox2D::OnAttach()
{
    m_Texture = CaelumRex::Texture2D::Create("assets/textures/Checkerboard.png");
}

void Sandbox2D::OnDetach()
{

}

void Sandbox2D::OnUpdate(CaelumRex::Timestep ts)
{
    m_CameraController.OnUpdate(ts);

    CaelumRex::Renderer2D::Begin(m_CameraController.GetCamera());
    CaelumRex::Renderer2D::DrawQuad({1.0f, 0.2f}, {0.3f, 0.3f}, {0.9f, 0.6f, 0.2f, 1.0f});
    CaelumRex::Renderer2D::DrawQuad({-1.0f, -0.8f}, {0.8f, 0.8f}, {0.2f, 0.8f, 0.4f, 1.0f});
    CaelumRex::Renderer2D::DrawQuad({0.0f, 0.1f, -0.1f}, {2.0f, 2.0f}, {0.4f, 0.1f, 0.9f, 1.0f}, m_Texture);
    CaelumRex::Renderer2D::End();
}

void Sandbox2D::OnImGuiRender()
{

}

void Sandbox2D::OnEvent(CaelumRex::Event& event)
{
    m_CameraController.OnEvent(event);
}
