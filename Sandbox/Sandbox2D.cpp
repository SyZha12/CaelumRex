#include "Sandbox2D.h"

#include "Instrumentor.h"
#include "glm/gtc/type_ptr.inl"


Sandbox2D::Sandbox2D()
    : Layer("Sandbox2D"), m_CameraController(1920 / 1080)
{
}

void Sandbox2D::OnAttach()
{
    CR_PROFILE_FUNCTION();

    m_Texture = CaelumRex::Texture2D::Create("assets/textures/Checkerboard.png");
}

void Sandbox2D::OnDetach()
{

}

void Sandbox2D::OnUpdate(CaelumRex::Timestep ts)
{
    CR_PROFILE_FUNCTION();

    {
        CR_PROFILE_SCOPE("Sandbox2D - CameraController OnUpdate");
        m_CameraController.OnUpdate(ts);
    }

    {
        CR_PROFILE_SCOPE("Sandbox2D - RendererDraw OnUpdate");
        CaelumRex::Renderer2D::Begin(m_CameraController.GetCamera());
        {
            CR_PROFILE_SCOPE("Sandbox2D - DrawQuad");
            CaelumRex::Renderer2D::DrawQuad({1.0f, 0.2f}, {0.3f, 0.3f}, {0.9f, 0.6f, 0.2f, 1.0f});
        }
        CaelumRex::Renderer2D::DrawQuad({-1.0f, -0.8f}, {0.8f, 0.8f}, m_Color);
        CaelumRex::Renderer2D::DrawQuad({0.0f, 0.1f, -0.1f}, {2.0f, 2.0f}, m_Texture);
        CaelumRex::Renderer2D::End();
    }
}

void Sandbox2D::OnImGuiRender()
{
    CR_PROFILE_FUNCTION();

    ImGui::Begin("Setting");
        ImGui::ColorEdit3("Color", glm::value_ptr(m_Color));
    ImGui::End();
}

void Sandbox2D::OnEvent(CaelumRex::Event& event)
{
    m_CameraController.OnEvent(event);
}
