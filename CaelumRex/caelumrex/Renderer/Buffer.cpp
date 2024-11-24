#include "Buffer.h"

#include "Core.h"
#include "Log.h"
#include "OpenGLBuffer.h"
#include "Renderer/Renderer.h"
#include "spdlog/fmt/bundled/chrono.h"

namespace CaelumRex
{
    VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size)
    {
        switch(Renderer::getCurrentAPI())
        {
        case RendererAPI::API::None:
            CR_CORE_ERROR("VertexBuffer: RendererAPI::None is currently not supported."); return nullptr;
        case RendererAPI::API::OpenGL:
            return new OpenGLVertexBuffer(vertices, size);
        }

        CR_CORE_ERROR("VertexBuffer: Unknown RendererAPI.");
        return nullptr;
    }

    IndexBuffer* IndexBuffer::Create(uint32_t* indices, const uint32_t size)
    {
        switch(Renderer::getCurrentAPI())
        {
        case RendererAPI::API::None:
            CR_CORE_ERROR("IndexBuffer: RendererAPI::None is currently not supported."); return nullptr;
        case RendererAPI::API::OpenGL:
            return new OpenGLIndexBuffer(indices, size);
        }

        CR_CORE_ERROR("IndexBuffer: Unknown RendererAPI.");
        return nullptr;
    }

}
