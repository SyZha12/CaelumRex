/* CaelumRex Libraries */
#include <OpenGL/OpenGLVertexArray.h>
#include <Debug/Instrumentor.h>
#include <Core/Log.h>

/* Third-Party Libraries & Co*/
#include <glad/glad.h>

namespace CaelumRex
{
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

        CR_CORE_ERROR("ShaderDataTypeToOpenGLBaseType(): Unknown ShaderDataType.");
        return 0;
    }

    OpenGLVertexArray::OpenGLVertexArray()
    {
        glCreateVertexArrays(1, &m_RendererID);
    }

    OpenGLVertexArray::~OpenGLVertexArray()
    {
        glDeleteVertexArrays(1, &m_RendererID);
    }

    void OpenGLVertexArray::Bind()
    {
        glBindVertexArray(m_RendererID);
    }

    void OpenGLVertexArray::Unbind()
    {
        glBindVertexArray(0);
    }

    void OpenGLVertexArray::AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer)
    {
        CR_PROFILE_FUNCTION();

        if(vertexBuffer->GetLayout().GetElements().size() == 0)
            CR_CORE_WARN("Vertex layout has not been set!");

        glBindVertexArray(m_RendererID);
        vertexBuffer->Bind();

        uint32_t index = 0;
        const auto& layout = vertexBuffer->GetLayout();
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

        m_VertexBuffers.push_back(vertexBuffer);
    }

    void OpenGLVertexArray::SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer)
    {
        glBindVertexArray(m_RendererID);
        indexBuffer->Bind();

        m_IndexBuffer = indexBuffer;
    }
}
