#ifndef OPENGLCONTEXT_H
#define OPENGLCONTEXT_H

#include "Renderer/GraphicsContext.h"
class GLFWwindow;

namespace CaelumRex
{
    class OpenGLContext : public GraphicsContext
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
