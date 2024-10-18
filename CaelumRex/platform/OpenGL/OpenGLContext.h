#ifndef OPENGLCONTEXT_H
#define OPENGLCONTEXT_H

#include "Renderer/RendererContext.h"
class GLFWwindow;

namespace CaelumRex
{
    class OpenGLContext : public RendererContext
    {
    public:
        OpenGLContext(GLFWwindow* windowHandle);

        void Init() override;
        void SwapBuffers() override;
    private:
        GLFWwindow* m_WindowHandle;
    };
}

#endif //OPENGLCONTEXT_H
