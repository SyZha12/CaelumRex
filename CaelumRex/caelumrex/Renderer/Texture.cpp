/** CaelumRex libraries **/
#include <Renderer/Texture.h>
#include <Renderer/Renderer.h>
#include <OpenGL/OpenGLTexture.h>

namespace CaelumRex
{
    Ref<Texture2D> Texture2D::Create(uint32_t width, uint32_t height)
    {
        switch(Renderer::getCurrentAPI())
        {
        case RendererAPI::API::None:
            CR_CORE_ERROR("Texture: RendererAPI::None is currently not supported."); return nullptr;
        case RendererAPI::API::OpenGL:
            return CreateRef<OpenGLTexture2D>(width, height);
        }

        CR_CORE_ERROR("Texture: Unknown RendererAPI.");
        return nullptr;
    }

    Ref<Texture2D> Texture2D::Create(const std::string& path)
    {
        switch(Renderer::getCurrentAPI())
        {
        case RendererAPI::API::None:
            CR_CORE_ERROR("Texture: RendererAPI::None is currently not supported."); return nullptr;
        case RendererAPI::API::OpenGL:
            return CreateRef<OpenGLTexture2D>(path);
        }

        CR_CORE_ERROR("Texture: Unknown RendererAPI.");
        return nullptr;
    }
}
