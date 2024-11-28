/** CaelumRex libraries **/
#include <Renderer/RenderCommand.h>
#include <OpenGL/OpenGLRendererAPI.h>

namespace CaelumRex
{
    RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI;

}
