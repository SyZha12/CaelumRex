#ifndef RENDERER_H
#define RENDERER_H

#include "Renderer/RenderCommand.h"

/**
 * Renderer class is used as the most top level class for rendering the environment, camera, light, objects, etc.
 */
namespace CaelumRex
{
    class Renderer
    {
    public:
        static void Begin();
        static void End();

        static void Dispatch(const std::shared_ptr<VertexArray>& vertexArray);

        static RendererAPI::API getCurrentAPI() { return RendererAPI::GetAPI(); }
    };
}

#endif //RENDERER_H
