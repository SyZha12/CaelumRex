/* CaelumRex Libraries */
#include <Renderer/RenderCommand.h>
#include <OpenGL/OpenGLRendererAPI.h>

namespace CaelumRex
{
    Ref<RendererAPI> RenderCommand::s_RendererAPI = std::make_unique<OpenGLRendererAPI>();

}
