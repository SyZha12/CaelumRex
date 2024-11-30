#ifndef RENDERER2D_H
#define RENDERER2D_H

/* CaelumRex Libraries */
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
        static void Flush();

        static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color);
        static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color);
        static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D>& texture);
        static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D>& texture);
        static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color, const Ref<Texture2D>& texture);
        static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color, const Ref<Texture2D>& texture);

        static void DrawRotationQuad(const glm::vec3& position, const glm::vec2& size, bool rotation, const glm::vec4& color);
    };
}

#endif //RENDERER2D_H
