#ifndef GraphicsCONTEXT_H
#define GraphicsCONTEXT_H

/** CaelumRex libraries **/
#include <Core/Core.h>

namespace CaelumRex
{
    class GraphicsContext
    {
    public:
        virtual void Init() = 0;
        virtual void SwapBuffers() = 0;

        static Scope<GraphicsContext> Create(void* window);
    };
}

#endif //GraphicsCONTEXT_H
