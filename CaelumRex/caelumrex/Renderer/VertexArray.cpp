#include "VertexArray.h"

#include "Core.h"
#include "OpenGLVertexArray.h"
#include "Renderer.h"

namespace CaelumRex
{
    VertexArray* VertexArray::Create()
    {
        switch(Renderer::getCurrentAPI())
        {
        case RendererAPI::None:
            CR_CORE_ASSERT(false, "RendererAPI::None is currently not supported."); return nullptr;
        case RendererAPI::OpenGL:
            return new OpenGLVertexArray();
        }

        CR_CORE_ASSERT(false, "Unknown RendererAPI.");
        return nullptr;
    }
}
