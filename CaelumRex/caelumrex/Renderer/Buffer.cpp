#include "Buffer.h"

#include "Core.h"
#include "OpenGLBuffer.h"
#include "Renderer/Renderer.h"

namespace CaelumRex
{
    VertexBuffer* VertexBuffer::Create(float* vertices, u_int32_t size)
    {
        switch(Renderer::getCurrentAPI())
        {
        case RendererAPI::None:
            CR_CORE_ASSERT(false, "RendererAPI::None is currently not supported."); return nullptr;
        case RendererAPI::OpenGL:
            return new OpenGLVertexBuffer(vertices, size);
        }

        CR_CORE_ASSERT(false, "Unknown RendererAPI.");
        return nullptr;
    }

    IndexBuffer* IndexBuffer::Create(u_int32_t* indices, u_int32_t size)
    {
        switch(Renderer::getCurrentAPI())
        {
        case RendererAPI::None:
            CR_CORE_ASSERT(false, "RendererAPI::None is currently not supported."); return nullptr;
        case RendererAPI::OpenGL:
            return new OpenGLIndexBuffer(indices, size);
        }

        CR_CORE_ASSERT(false, "Unknown RendererAPI.");
        return nullptr;
    }

}