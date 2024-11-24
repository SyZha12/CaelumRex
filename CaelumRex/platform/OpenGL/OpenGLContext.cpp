#include "OpenGLContext.h"

#include "Core/Core.h"
#include "Core/Log.h"
#define GLFW_INCLUDE_NONE
#include "glad/glad.h"
#include "GLFW/glfw3.h"

namespace CaelumRex
{
    OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
        : m_WindowHandle(windowHandle)
    {
        if(windowHandle)
            CR_CORE_ERROR("Window handle is null.");
    }

    void OpenGLContext::Init()
    {
        // Make current GLFW context current
        glfwMakeContextCurrent(m_WindowHandle);
        // Load GL (glad)
        if(gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
            CR_CORE_ERROR("Failed to initialize Glad");
        CR_CORE_INFO("GLAD initialized");

        CR_CORE_INFO("OpenGL Info:");
        CR_CORE_INFO("Vendor: {0}", (char*)glGetString(GL_VENDOR));
        CR_CORE_INFO("Renderer: {0}", (char*)glGetString(GL_RENDERER));
        CR_CORE_INFO("Version: {0}", (char*)glGetString(GL_VERSION));
    }

    void OpenGLContext::SwapBuffers()
    {
        glfwSwapBuffers(m_WindowHandle);

        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
    }
}
