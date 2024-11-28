/** CaelumRex libraries **/
#include <Renderer/GraphicsContext.h>
#include <Core/Core.h>
#include <OpenGL/OpenGLContext.h>
#include <Renderer/Renderer.h>

namespace CaelumRex
{
    Scope<GraphicsContext> GraphicsContext::Create(void* window)
    {
        switch (Renderer::getCurrentAPI())
        {
        case RendererAPI::API::None:
            CR_CORE_ERROR("GraphicsContext: GraphicsContext::None is currently not supported."); return nullptr;
        case RendererAPI::API::OpenGL:
            return CreateScope<OpenGLContext>(static_cast<GLFWwindow*>(window));
        }

        CR_CORE_ERROR("GraphicsContext: Unknown RendererAPI.");
        return nullptr;
    }
}
