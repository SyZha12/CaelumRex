#include "Renderer.h"

namespace CaelumRex
{
    void Renderer::Begin()
    {
    }

    void Renderer::End()
    {
    }

    void Renderer::Dispatch(const std::shared_ptr<VertexArray>& vertexArray)
    {
        vertexArray->Bind();
        RenderCommand::DrawIndexed(vertexArray);
    }
}
