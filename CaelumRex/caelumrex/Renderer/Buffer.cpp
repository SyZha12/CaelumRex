/* CaelumRex Libraries */
#include <Renderer/Buffer.h>
#include <Core/Log.h>
#include <OpenGL/OpenGLBuffer.h>
#include <Renderer/Renderer.h>

namespace CaelumRex
{
    Ref<VertexBuffer> VertexBuffer::Create(uint32_t size)
    {
        switch(Renderer::getCurrentAPI())
        {
        case RendererAPI::API::None:
            CR_CORE_ERROR("VertexBuffer: RendererAPI::None is currently not supported."); return nullptr;
        case RendererAPI::API::OpenGL:
            return CreateRef<OpenGLVertexBuffer>(size);
        }

        CR_CORE_ERROR("VertexBuffer: Unknown RendererAPI.");
        return nullptr;
    }

    Ref<VertexBuffer> VertexBuffer::Create(float* vertices, uint32_t size)
    {
        switch(Renderer::getCurrentAPI())
        {
        case RendererAPI::API::None:
            CR_CORE_ERROR("VertexBuffer: RendererAPI::None is currently not supported."); return nullptr;
        case RendererAPI::API::OpenGL:
            return CreateRef<OpenGLVertexBuffer>(vertices, size);
        }

        CR_CORE_ERROR("VertexBuffer: Unknown RendererAPI.");
        return nullptr;
    }

    Ref<IndexBuffer> IndexBuffer::Create(uint32_t* indices, const uint32_t size)
    {
        switch(Renderer::getCurrentAPI())
        {
        case RendererAPI::API::None:
            CR_CORE_ERROR("IndexBuffer: RendererAPI::None is currently not supported."); return nullptr;
        case RendererAPI::API::OpenGL:
            return CreateRef<OpenGLIndexBuffer>(indices, size);
        }

        CR_CORE_ERROR("IndexBuffer: Unknown RendererAPI.");
        return nullptr;
    }

}
