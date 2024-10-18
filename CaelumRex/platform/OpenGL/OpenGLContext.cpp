#include "OpenGLContext.h"

#define GLFW_INCLUDE_NONE
#include "glad/glad.h"
#include "GLFW/glfw3.h"

namespace CaelumRex
{
    OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
        : m_WindowHandle(windowHandle)
    {
        CR_CORE_ASSERT(windowHandle, "Window handle is null.")
    }

    void OpenGLContext::Init()
    {
        // Make current GLFW context current
        glfwMakeContextCurrent(m_WindowHandle);
        // Load GL (glad)
        int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
        CR_CORE_ASSERT(status, "Failed to initialize Glad")


    }

    void OpenGLContext::SwapBuffers()
    {
        glfwSwapBuffers(m_WindowHandle);

        glClearColor(1.0f, 0.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
    }
}
