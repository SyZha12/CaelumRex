#include "Sandbox2D.h"

#include "Instrumentor.h"
#include "glm/gtc/type_ptr.inl"
#include <imgui-docking/imgui.h>

Sandbox2D::Sandbox2D()
    : Layer("Sandbox2D"), m_CameraController(1920 / 1080)
{
}

void Sandbox2D::OnAttach()
{
    CR_PROFILE_FUNCTION();

    m_Texture = CaelumRex::Texture2D::Create("Sandbox/assets/textures/Checkerboard.png");
    m_TextureLogo = CaelumRex::Texture2D::Create("Sandbox/assets/textures/c++.png");
}

void Sandbox2D::OnDetach()
{

}

void Sandbox2D::OnUpdate(CaelumRex::Timestep ts)
{
    CR_PROFILE_FUNCTION();

    CaelumRex::RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1.0f});
    CaelumRex::RenderCommand::Clear();

    {
        CR_PROFILE_SCOPE("Sandbox2D - CameraController OnUpdate");
        m_CameraController.OnUpdate(ts);
    }

    {
        CR_PROFILE_SCOPE("Sandbox2D - RendererDraw OnUpdate");
        CaelumRex::Renderer2D::Begin(m_CameraController.GetCamera());
        {
            CR_PROFILE_SCOPE("Sandbox2D - DrawQuad");
            CaelumRex::Renderer2D::DrawQuad(m_Position, {0.3f, 0.3f}, {0.9f, 0.6f, 0.2f, 1.0f});
            CaelumRex::Renderer2D::DrawQuad({-0.9f, -0.9f}, {0.9f, 1.1f}, m_TextureLogo);
            CaelumRex::Renderer2D::DrawQuad({-0.9f, 0.9f}, {0.5f, 0.5f}, m_Color);
        }
        // m_CameraController.EnableRotation(true);
        // CaelumRex::Renderer2D::DrawRotationQuad({-1.0f, -0.8f, 0.0f}, {0.8f, 0.8f}, true, m_Color);
        CaelumRex::Renderer2D::DrawQuad({0.0f, 0.1f}, {0.8f, 0.8f}, m_Texture);
        CaelumRex::Renderer2D::End();
    }
}

void Sandbox2D::OnImGuiRender()
{
    CR_PROFILE_FUNCTION();

    ImGui::Begin("Setting");
        ImGui::ColorEdit3("Color", glm::value_ptr(m_Color));
        ImGui::SliderFloat2("Position", value_ptr(m_Position), m_Position.x, m_Position.y);
    ImGui::End();
}

void Sandbox2D::OnEvent(CaelumRex::Event& event)
{
    m_CameraController.OnEvent(event);
}
