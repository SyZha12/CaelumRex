#ifndef RENDERERAPI_H
#define RENDERERAPI_H

/**
 *  @brief RendererAPI is a pure virtual class and should be overridden by the OpenGLRendererAPI (or in the future
 *         VulkanRendererAPI). This decides after Renderer and RenderCommands which platform to use; i.e. OpenGL API
 *         or in the future Vulkan API
 */

/* CaelumRex Libraries */
#include <Renderer/VertexArray.h>

/* Third-Party Libraries & Co*/
#include <glm/glm.hpp>

namespace CaelumRex
{
    class RendererAPI
    {
    public:
        enum class API
        {
            None = 0, OpenGL = 1
        };

        virtual void Init() = 0;

        virtual void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) = 0;

        virtual void SetClearColor(const glm::vec4& color) = 0;
        virtual void Clear() = 0;

        virtual void DrawIndexed(const Ref<VertexArray>& vertexArray) = 0;

        static API GetAPI() { return s_API; }
    private:
        static API s_API;
    };
}

#endif //RENDERERAPI_H
