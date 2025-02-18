/* CaelumRex Libraries */
#include <Renderer/Renderer.h>
#include <OpenGL/OpenGLShader.h>
#include <Renderer/Renderer2D.h>

namespace CaelumRex
{
    // Scope<Renderer::SceneData> Renderer::m_SceneData = CreateScope<SceneData>();

    void Renderer::Init()
    {
        RenderCommand::Init();
        Renderer2D::Init();
    }

    void Renderer::OnWindowResize(uint32_t width, uint32_t height)
    {
        RenderCommand::SetViewport(0, 0, width, height);
    }

    // void Renderer::Begin(OrthographicCamera& camera)
    // {
    //     m_SceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
    // }
    //
    // void Renderer::End()
    // {
    // }

    // void Renderer::Dispatch(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray, const glm::mat4& transform)
    // {
    //     shader->Bind();
    //     std::dynamic_pointer_cast<OpenGLShader>(shader)->SetUniformMat4("u_ViewProjection", m_SceneData->ViewProjectionMatrix);
    //     std::dynamic_pointer_cast<OpenGLShader>(shader)->SetUniformMat4("u_Transform", transform);
    //
    //     vertexArray->Bind();
    //     RenderCommand::DrawIndexed(vertexArray);
    // }
}
