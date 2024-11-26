#ifndef RENDERER_H
#define RENDERER_H

#include "Camera.h"
#include "Shader.h"
#include "Renderer/RenderCommand.h"

/**
 * Renderer class is used as the most top level class for rendering the environment, camera, light, objects, etc.
 */
namespace CaelumRex
{
    class Renderer
    {
    public:
        static void Begin(OrthographicCamera& camera);
        static void End();

        static void Dispatch(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray, const glm::mat4& transform = glm::mat4(1.0f));

        static RendererAPI::API getCurrentAPI() { return RendererAPI::GetAPI(); }
    private:
        struct SceneData
        {
            glm::mat4 ViewProjectionMatrix;
        };

        static SceneData* m_SceneData;
    };
}

#endif //RENDERER_H
