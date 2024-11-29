/** CaelumRex libraries **/
#include <Renderer/Renderer2D.h>
#include <Renderer/Shader.h>
#include <Renderer/VertexArray.h>
#include <Renderer/RenderCommand.h>

#define GLM_ENABLE_EXPERIMENTAL
#include "glm/gtx/transform.hpp"

namespace CaelumRex
{
    struct DataStorage
    {
        Ref<VertexArray> QuadVertexArray;
        Ref<Shader> QuadShader;
    };

    static DataStorage* s_DataStorage;

    void Renderer2D::Init()
    {
        s_DataStorage = new DataStorage();

        s_DataStorage->QuadVertexArray = VertexArray::Create();
        float vertices[] = {
            -0.5f,  0.5f, 0.0f,
             0.5f,  0.5f, 0.0f,
            -0.5f, -0.5f, 0.0f,
             0.5f, -0.5f, 0.0f
        };
        Ref<VertexBuffer> m_2DVertexBuffer = VertexBuffer::Create(vertices, sizeof(vertices));
        m_2DVertexBuffer->SetLayout({
            { ShaderDataType::Float3, "v_Position" }
        });
        s_DataStorage->QuadVertexArray->AddVertexBuffer(m_2DVertexBuffer);

        uint32_t indices[] = { 0, 1, 2, 1, 2, 3 };
        Ref<IndexBuffer> m_2DIndexBuffer = IndexBuffer::Create(indices, sizeof(indices));
        s_DataStorage->QuadVertexArray->SetIndexBuffer(m_2DIndexBuffer);

        s_DataStorage->QuadShader = Shader::Create("assets/shaders/BasicShader.glsl");
    }

    void Renderer2D::Shutdown()
    {
        delete s_DataStorage;
    }

    void Renderer2D::Begin(const OrthographicCamera& camera)
    {
        s_DataStorage->QuadShader->Bind();
        s_DataStorage->QuadShader->SetMat4("u_ViewProjection", camera.GetViewProjectionMatrix());
    }

    void Renderer2D::End()
    {
    }

    void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color)
    {
        DrawQuad({position.x, position.y, 0.0f}, size, color);
    }

    void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color)
    {
        s_DataStorage->QuadShader->Bind();
        s_DataStorage->QuadShader->SetFloat4("u_Color", color);

        glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), {size.x, size.y, 1.0f}) /* rotation */;
        s_DataStorage->QuadShader->SetMat4("u_Transform", transform);

        s_DataStorage->QuadVertexArray->Bind();
        RenderCommand::DrawIndexed(s_DataStorage->QuadVertexArray);
    }

    void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D>& texture)
    {
        DrawQuad({position.x, position.y, 0.0f}, size, texture);
    }

    void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D>& texture)
    {
        s_DataStorage->QuadShader->Bind();
        s_DataStorage->QuadShader->SetFloat4("u_Color", texture);

        glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), {size.x, size.y, 1.0f}) /* rotation */;
        s_DataStorage->QuadShader->SetMat4("u_Transform", transform);

        s_DataStorage->QuadVertexArray->Bind();
        RenderCommand::DrawIndexed(s_DataStorage->QuadVertexArray);
    }
}
