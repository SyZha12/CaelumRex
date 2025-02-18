/* CaelumRex Libraries */
#include <Renderer/Renderer2D.h>
#include <Renderer/Shader.h>
#include <Renderer/VertexArray.h>
#include <Renderer/RenderCommand.h>

#define GLM_ENABLE_EXPERIMENTAL
#include "Instrumentor.h"
#include "glm/gtx/transform.hpp"

namespace CaelumRex
{
    struct QuadVertex
    {
        glm::vec3 Position;
        glm::vec4 Color;
        glm::vec2 TextureCoordination;
        float TextureIndex;
    };

    struct DataStorage
    {
        const uint32_t MaxQuads =  10000;
        const uint32_t MaxVertices = MaxQuads * 4;
        const uint32_t MaxIndices = MaxQuads * 6;
        static constexpr uint32_t MaxTextureSlots = 32; // TODO: RenderCaps

        Ref<VertexArray> QuadVertexArray;
        Ref<VertexBuffer> QuadVertexBuffer;
        Ref<Shader> BasicShader;
        Ref<Texture2D> WhiteTexture;

        uint32_t QuadIndexCount = 0;
        QuadVertex* QuadVertexBufferBase = nullptr;
        QuadVertex* QuadVertexBufferPtr = nullptr;

        std::array<Ref<Texture2D>, MaxTextureSlots> TextureSlots;
        uint32_t TextureSlotIndex = 1;  // 0 is white texture
    };

    static DataStorage s_DataStorage;

    void Renderer2D::Init()
    {
        CR_PROFILE_FUNCTION();

        s_DataStorage.QuadVertexArray = VertexArray::Create();

        s_DataStorage.QuadVertexBuffer = VertexBuffer::Create(s_DataStorage.MaxVertices * sizeof(QuadVertex));
        s_DataStorage.QuadVertexBuffer->SetLayout({
            { ShaderDataType::Float3, "a_Position" },
            { ShaderDataType::Float4, "a_Color" },
            { ShaderDataType::Float2, "a_TexCoord"},
            { ShaderDataType::Float , "a_TexIndex"}
        });
        s_DataStorage.QuadVertexArray->AddVertexBuffer(s_DataStorage.QuadVertexBuffer);

        s_DataStorage.QuadVertexBufferBase = new QuadVertex[s_DataStorage.MaxVertices];

        {
            CR_PROFILE_SCOPE("Renderer2D - Init Indices");

            uint32_t* quadIndices = new uint32_t[s_DataStorage.MaxIndices];

            uint32_t offset = 0;
            for(uint32_t i = 0; i < s_DataStorage.MaxIndices; i += 6)
            {
                quadIndices[i + 0] = offset + 0;
                quadIndices[i + 1] = offset + 1;
                quadIndices[i + 2] = offset + 2;

                quadIndices[i + 3] = offset + 2;
                quadIndices[i + 4] = offset + 3;
                quadIndices[i + 5] = offset + 0;

                offset += 4;
            }

            Ref<IndexBuffer> m_2DIndexBuffer = IndexBuffer::Create(quadIndices, s_DataStorage.MaxIndices);
            s_DataStorage.QuadVertexArray->SetIndexBuffer(m_2DIndexBuffer);
            delete[] quadIndices;
        }

        // Set standard white texture, if no texture was set; white texture is always TextureSlot[0]
        s_DataStorage.WhiteTexture = Texture2D::Create(1, 1);
        uint32_t WhiteTextureData = 0xffffffff;
        s_DataStorage.WhiteTexture->SetData(&WhiteTextureData, sizeof(WhiteTextureData));

        int32_t samplers[s_DataStorage.MaxTextureSlots];
        for(uint32_t i = 0; i < s_DataStorage.MaxTextureSlots; i++)
            samplers[i] = i;

        s_DataStorage.BasicShader = Shader::Create("Sandbox/assets/shaders/BasicShader.glsl");
        s_DataStorage.BasicShader->Bind();
        s_DataStorage.BasicShader->SetIntArray("u_Textures", samplers, s_DataStorage.MaxTextureSlots);

        // Initialize texture slot to 0
        s_DataStorage.TextureSlots[0] = s_DataStorage.WhiteTexture;


    }

    void Renderer2D::Shutdown()
    {
        delete[] s_DataStorage.QuadVertexBufferBase;
        delete[] s_DataStorage.QuadVertexBufferPtr;
    }

    void Renderer2D::Begin(const OrthographicCamera& camera)
    {
        CR_PROFILE_FUNCTION();

        s_DataStorage.BasicShader->Bind();
        s_DataStorage.BasicShader->SetMat4("u_ViewProjection", camera.GetViewProjectionMatrix());

        s_DataStorage.QuadIndexCount = 0;
        s_DataStorage.QuadVertexBufferPtr = s_DataStorage.QuadVertexBufferBase;

        s_DataStorage.TextureSlotIndex = 1;
    }

    void Renderer2D::End()
    {
        CR_PROFILE_FUNCTION();

        const uint32_t dataSize = reinterpret_cast<uint8_t*>(s_DataStorage.QuadVertexBufferPtr) - reinterpret_cast<uint8_t*>(s_DataStorage.QuadVertexBufferBase);
        s_DataStorage.QuadVertexBuffer->SetData(s_DataStorage.QuadVertexBufferBase, dataSize);

        Flush();
    }

    void Renderer2D::Flush()
    {
        for(uint32_t i = 0; i < s_DataStorage.TextureSlotIndex; i++)
            s_DataStorage.TextureSlots[i]->Bind(i);

        RenderCommand::DrawIndexed(s_DataStorage.QuadVertexArray, s_DataStorage.QuadIndexCount);
    }

    void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color)
    {
        DrawQuad({position.x, position.y, 0.0f}, size, color);
    }

    void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color)
    {
        CR_PROFILE_FUNCTION();

        constexpr glm::vec2 textureCoordination = { 0.0f, 0.0f };
        constexpr float textureIndex = 0.0f; // White Texture

        s_DataStorage.QuadVertexBufferPtr->Position = position;
        s_DataStorage.QuadVertexBufferPtr->Color = color;
        s_DataStorage.QuadVertexBufferPtr->TextureCoordination = textureCoordination;
        s_DataStorage.QuadVertexBufferPtr->TextureIndex = textureIndex;
        s_DataStorage.QuadVertexBufferPtr++;

        s_DataStorage.QuadVertexBufferPtr->Position = { position.x + size.x, position.y, 0.0f };
        s_DataStorage.QuadVertexBufferPtr->Color = color;
        s_DataStorage.QuadVertexBufferPtr->TextureCoordination = textureCoordination;
        s_DataStorage.QuadVertexBufferPtr->TextureIndex = textureIndex;
        s_DataStorage.QuadVertexBufferPtr++;

        s_DataStorage.QuadVertexBufferPtr->Position = { position.x + size.x, position.y + size.y, 0.0f };
        s_DataStorage.QuadVertexBufferPtr->Color = color;
        s_DataStorage.QuadVertexBufferPtr->TextureCoordination = textureCoordination;
        s_DataStorage.QuadVertexBufferPtr->TextureIndex = textureIndex;
        s_DataStorage.QuadVertexBufferPtr++;

        s_DataStorage.QuadVertexBufferPtr->Position = { position.x, position.y + size.y, 0.0f };
        s_DataStorage.QuadVertexBufferPtr->Color = color;
        s_DataStorage.QuadVertexBufferPtr->TextureCoordination = textureCoordination;
        s_DataStorage.QuadVertexBufferPtr->TextureIndex = textureIndex;
        s_DataStorage.QuadVertexBufferPtr++;

        s_DataStorage.QuadIndexCount += 6;
    }

    void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D>& texture)
    {
        DrawQuad({position.x, position.y, 0.0f}, size, texture);
    }

    void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D>& texture)
    {
        CR_PROFILE_FUNCTION();

        constexpr glm::vec4 color = { 1.0f, 1.0f, 1.0f, 1.0f };

        float textureIndex = 0.0f;

        // Loop through all the set TextureSlotIndex numbers;
        for(uint32_t i = 0; i < s_DataStorage.TextureSlotIndex; i++)
        {
            if(*s_DataStorage.TextureSlots[i].get() == *texture.get())
            {
                textureIndex = (float)i;
                break;
            }
        }

        if(textureIndex == 0.0f)
        {
            textureIndex = (float)s_DataStorage.TextureSlotIndex;
            s_DataStorage.TextureSlots[s_DataStorage.TextureSlotIndex] = texture;
            s_DataStorage.TextureSlotIndex++;
        }

        s_DataStorage.QuadVertexBufferPtr->Position = position;
        s_DataStorage.QuadVertexBufferPtr->Color = color;
        s_DataStorage.QuadVertexBufferPtr->TextureCoordination = { 0.0f, 0.0f };
        s_DataStorage.QuadVertexBufferPtr->TextureIndex = textureIndex;
        s_DataStorage.QuadVertexBufferPtr++;

        s_DataStorage.QuadVertexBufferPtr->Position = { position.x + size.x, position.y, 0.0f };
        s_DataStorage.QuadVertexBufferPtr->Color = color;
        s_DataStorage.QuadVertexBufferPtr->TextureCoordination = { 1.0f, 0.0f };
        s_DataStorage.QuadVertexBufferPtr->TextureIndex = textureIndex;
        s_DataStorage.QuadVertexBufferPtr++;

        s_DataStorage.QuadVertexBufferPtr->Position = { position.x + size.x, position.y + size.y, 0.0f };
        s_DataStorage.QuadVertexBufferPtr->Color = color;
        s_DataStorage.QuadVertexBufferPtr->TextureCoordination = { 1.0f, 1.0f };
        s_DataStorage.QuadVertexBufferPtr->TextureIndex = textureIndex;
        s_DataStorage.QuadVertexBufferPtr++;

        s_DataStorage.QuadVertexBufferPtr->Position = { position.x, position.y + size.y, 0.0f };
        s_DataStorage.QuadVertexBufferPtr->Color = color;
        s_DataStorage.QuadVertexBufferPtr->TextureCoordination = { 0.0f, 1.0f };
        s_DataStorage.QuadVertexBufferPtr->TextureIndex = textureIndex;
        s_DataStorage.QuadVertexBufferPtr++;

        s_DataStorage.QuadIndexCount += 6;

    }

    void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color, const Ref<Texture2D>& texture)
    {
        DrawQuad({position.x, position.y, 0.0f}, size, color, texture);
    }

    void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color, const Ref<Texture2D>& texture)
    {
        CR_PROFILE_FUNCTION();
        
        glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), {size.x, size.y, 1.0f}) /* rotation */;

        s_DataStorage.BasicShader->SetMat4("u_Transform", transform);
        s_DataStorage.BasicShader->SetFloat4("u_Color", color);

        texture->Bind();

        s_DataStorage.QuadVertexArray->Bind();
        RenderCommand::DrawIndexed(s_DataStorage.QuadVertexArray);
    }

    void Renderer2D::DrawRotationQuad(const glm::vec3& position, const glm::vec2& size, bool rotation, const glm::vec4& color)
    {
        glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), {size.x, size.y, 1.0f}) * glm::rotate(glm::mat4(1.0f), glm::radians(-15.0f), glm::vec3(1.0f))/* rotation */;

        s_DataStorage.BasicShader->SetMat4("u_Transform", transform);
        s_DataStorage.BasicShader->SetFloat4("u_Color", color);

        s_DataStorage.WhiteTexture->Bind();

        s_DataStorage.QuadVertexArray->Bind();
        RenderCommand::DrawIndexed(s_DataStorage.QuadVertexArray);
    }
}
