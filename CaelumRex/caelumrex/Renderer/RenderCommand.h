#ifndef RENDERCOMMAND_H
#define RENDERCOMMAND_H

#include "Renderer/RendererAPI.h"

/**
 * RenderCommands should only do one thing at a time and draws from the Renderer class itself
 */
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

        static void SetClearColor(const glm::vec4& color)
        {
            s_RendererAPI->SetClearColor(color);
        }
        static void Clear()
        {
            s_RendererAPI->Clear();
        }

        static void DrawIndexed(const Ref<VertexArray>& vertexArray)
        {
            s_RendererAPI->DrawIndexed(vertexArray);
        }
    private:
        static RendererAPI* s_RendererAPI;
    };

}


#endif //RENDERCOMMAND_H
