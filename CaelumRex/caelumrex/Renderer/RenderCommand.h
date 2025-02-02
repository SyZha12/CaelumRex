#ifndef RENDERCOMMAND_H
#define RENDERCOMMAND_H

/**
 *  @brief RenderCommands should only do one thing at a time and draws from the Renderer class itself
 */

/* CaelumRex Libraries */
#include <Renderer/RendererAPI.h>

namespace CaelumRex
{
    // RenderCommands should only do one thing
    class RenderCommand
    {
    public:
        static void Init()
        {
            s_RendererAPI->Init();
        }

        // Used for setWindowResize
        static void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
        {
            s_RendererAPI->SetViewport(x, y, width, height);
        }

        static void SetClearColor(const glm::vec4& color)
        {
            s_RendererAPI->SetClearColor(color);
        }
        static void Clear()
        {
            s_RendererAPI->Clear();
        }

        static void DrawIndexed(const Ref<VertexArray>& vertexArray, uint32_t indexCount = 0)
        {
            s_RendererAPI->DrawIndexed(vertexArray, indexCount);
        }
    private:
        static Ref<RendererAPI> s_RendererAPI;
    };

}


#endif //RENDERCOMMAND_H
