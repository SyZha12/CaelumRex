#ifndef RENDERER2D_H
#define RENDERER2D_H

/** CaelumRex libraries **/
#include <Renderer/Camera.h>
#include <Renderer/Texture.h>

namespace CaelumRex
{
    class Renderer2D
    {
    public:
        static void Init();
        static void Shutdown();

        static void Begin(const OrthographicCamera& camera);
        static void End();

        static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color);
        static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color);
        static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D>& texture);
        static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D>& texture);
        static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color, const Ref<Texture2D>& texture);
        static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color, const Ref<Texture2D>& texture);
    };
}

#endif //RENDERER2D_H
