#ifndef RENDERERCONTEXT_H
#define RENDERERCONTEXT_H

namespace CaelumRex
{
    class RendererContext
    {
    public:
        virtual void Init() = 0;
        virtual void SwapBuffers() = 0;
    };
}

#endif //RENDERERCONTEXT_H
