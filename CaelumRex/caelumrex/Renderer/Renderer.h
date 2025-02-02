#ifndef RENDERER_H
#define RENDERER_H

/**
 *  TODO Make class that can be inherited by the 2D and 3D renderer
 */

/* CaelumRex Libraries */
#include <Renderer/Camera.h>
#include <Renderer/Shader.h>
#include <Renderer/RenderCommand.h>

namespace CaelumRex
{
    class Renderer
    {
    public:
        static void Init();

        static void OnWindowResize(uint32_t width, uint32_t height);

        // static void Begin(OrthographicCamera& camera);
        // static void End();

        // static void Dispatch(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray, const glm::mat4& transform = glm::mat4(1.0f));

        static RendererAPI::API getCurrentAPI() { return RendererAPI::GetAPI(); }
    private:
        // struct SceneData
        // {
        //     glm::mat4 ViewProjectionMatrix;
        // };

        // static Scope<SceneData> m_SceneData;
    };
}

#endif //RENDERER_H
