#ifndef RENDERER_H
#define RENDERER_H

namespace CaelumRex
{
    enum class RendererAPI
    {
        None = 0, OpenGL = 1
    };

    class Renderer
    {
    public:
        static RendererAPI getCurrentAPI() { return s_RendererAPI; }
    private:
        static RendererAPI s_RendererAPI;
    };
}

#endif //RENDERER_H
