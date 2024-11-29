/* CaelumRex Libraries */
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
        Ref<VertexArray> vertexArray;
        Ref<Shader> shader;
        Ref<Texture2D> whiteTexture;
    };

    static DataStorage* s_DataStorage;

    void Renderer2D::Init()
    {
        s_DataStorage = new DataStorage();

        s_DataStorage->vertexArray = VertexArray::Create();
        float vertices[] = {
            -0.5f,  0.5f, 0.0f, 0.0f,  1.0f,
             0.5f,  0.5f, 0.0f, 1.0f,  1.0f,
            -0.5f, -0.5f, 0.0f, 0.0f,  0.0f,
             0.5f, -0.5f, 0.0f, 1.0f,  0.0f
        };
        Ref<VertexBuffer> m_2DVertexBuffer = VertexBuffer::Create(vertices, sizeof(vertices));
        m_2DVertexBuffer->SetLayout({
            { ShaderDataType::Float3, "a_Position" },
            { ShaderDataType::Float2, "a_TexCoord"}
        });
        s_DataStorage->vertexArray->AddVertexBuffer(m_2DVertexBuffer);

        uint32_t indices[] = { 0, 1, 2, 1, 2, 3 };
        Ref<IndexBuffer> m_2DIndexBuffer = IndexBuffer::Create(indices, sizeof(indices));
        s_DataStorage->vertexArray->SetIndexBuffer(m_2DIndexBuffer);

        s_DataStorage->whiteTexture = Texture2D::Create(1, 1);
        uint32_t whiteTextureData = 0xffffffff;
        s_DataStorage->whiteTexture->SetData(&whiteTextureData, sizeof(whiteTextureData));
        s_DataStorage->shader = Shader::Create("assets/shaders/BasicShader.glsl");
        s_DataStorage->shader->Bind();
        s_DataStorage->shader->SetInt("u_Texture", 0);
    }

    void Renderer2D::Shutdown()
    {
        delete s_DataStorage;
    }

    void Renderer2D::Begin(const OrthographicCamera& camera)
    {
        s_DataStorage->shader->Bind();
        s_DataStorage->shader->SetMat4("u_ViewProjection", camera.GetViewProjectionMatrix());
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
        glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), {size.x, size.y, 1.0f}) /* rotation */;

        s_DataStorage->shader->SetMat4("u_Transform", transform);
        s_DataStorage->shader->SetFloat4("u_Color", color);

        s_DataStorage->whiteTexture->Bind();

        s_DataStorage->vertexArray->Bind();
        RenderCommand::DrawIndexed(s_DataStorage->vertexArray);
    }

    void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D>& texture)
    {
        DrawQuad({position.x, position.y, 0.0f}, size, texture);
    }

    void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D>& texture)
    {
        glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), {size.x, size.y, 1.0f}) /* rotation */;

        s_DataStorage->shader->SetMat4("u_Transform", transform);
        s_DataStorage->shader->SetFloat4("u_Color", glm::vec4(1.0f));

        texture->Bind();

        s_DataStorage->vertexArray->Bind();
        RenderCommand::DrawIndexed(s_DataStorage->vertexArray);
    }

    void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color, const Ref<Texture2D>& texture)
    {
        DrawQuad({position.x, position.y, 0.0f}, size, color, texture);
    }

    void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color, const Ref<Texture2D>& texture)
    {
        glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), {size.x, size.y, 1.0f}) /* rotation */;

        s_DataStorage->shader->SetMat4("u_Transform", transform);
        s_DataStorage->shader->SetFloat4("u_Color", color);

        texture->Bind();

        s_DataStorage->vertexArray->Bind();
        RenderCommand::DrawIndexed(s_DataStorage->vertexArray);
    }
}
