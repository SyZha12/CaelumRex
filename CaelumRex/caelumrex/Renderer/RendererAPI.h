#ifndef RENDERERAPI_H
#define RENDERERAPI_H

#include <memory>
#include <glm/glm.hpp>

#include "VertexArray.h"

/**
 * RendererAPI is a pure virtual class and should be overridden by the OpenGLRendererAPI (or in the future VulkanRendererAPI)
 * This decides after Renderer and RenderCommands which platform to use; i.e. OpenGL API or in the future Vulkan API
 */

namespace CaelumRex
{
    class RendererAPI
    {
    public:
        enum class API
        {
            None = 0, OpenGL = 1
        };

        virtual void SetClearColor(const glm::vec4& color) = 0;
        virtual void Clear() = 0;

        virtual void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray) = 0;

        static API GetAPI() { return s_API; }
    private:
        static API s_API;
    };
}

#endif //RENDERERAPI_H
