/* CaelumRex Libraries */
#include <Renderer/VertexArray.h>
#include <Core/Core.h>
#include <OpenGL/OpenGLVertexArray.h>
#include <Renderer/Renderer.h>

namespace CaelumRex
{
    Ref<VertexArray> VertexArray::Create()
    {
        switch(Renderer::getCurrentAPI())
        {
        case RendererAPI::API::None:
            CR_CORE_ERROR("VertexArray: RendererAPI::None is currently not supported."); return nullptr;
        case RendererAPI::API::OpenGL:
            return CreateRef<OpenGLVertexArray>();
        }

        CR_CORE_ERROR("VertexArray: Unknown RendererAPI.");
        return nullptr;
    }
}
