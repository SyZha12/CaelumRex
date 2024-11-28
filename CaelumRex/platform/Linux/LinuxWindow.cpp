#include "Linux/LinuxWindow.h"

#include "Renderer.h"
#include "Events/ApplicationEvent.h"
#include "Events/KeyEvent.h"
#include "Events/MouseEvent.h"
#include "OpenGL/OpenGLContext.h"

namespace CaelumRex
{
    LinuxWindow::LinuxWindow(const WindowProperties& props)
        : m_Window(nullptr)
    {
        Init(props);
    }

    LinuxWindow::~LinuxWindow()
    {
        ShutDown();
    }

    void LinuxWindow::Init(const WindowProperties& props)
    {
        m_WindowData.Title = props.Title;
        m_WindowData.Width = props.Width;
        m_WindowData.Height = props.Height;
        CR_CORE_INFO("Creating window {0} ({1}, {2})", props.Title, props.Width, props.Height);

        if(!s_GLFWInitialized)
        {
            // Initialize the glfw library
            if(!glfwInit())
                CR_CORE_ERROR("Could not initialize GLFW!");
            glfwSetErrorCallback(GLFWErrorCallBack);

            s_GLFWInitialized = true;
        }

        // Create GLFW window
        m_Window = glfwCreateWindow(
            static_cast<int>(props.Width),
            static_cast<int>(props.Height),
            props.Title.c_str(),
            nullptr,
            nullptr
            );

        // Create new OpenGL context
        m_Context = GraphicsContext::Create(m_Window);
        m_Context->Init();

        // Sets the user-defined pointer of the specified window. The current value is retained until the window is destroyed
        // What this means is on that GLFWwindow is a struct that has a place for any data we want and set it to the m_WindowData struct
        glfwSetWindowUserPointer(m_Window, &m_WindowData);
        SetVSync(true);

        SetCallBacks();
    }

    void LinuxWindow::ShutDown()
    {
        glfwDestroyWindow(m_Window);
    }

    void LinuxWindow::OnUpdate()
    {
        glfwPollEvents();
        m_Context->SwapBuffers();
    }

    void LinuxWindow::SetCallBacks() const
    {
        // typedef void(*GLFWwindowsizefun)(GLFWwindow * window, int width, int height)
        // value: void(*) (GLFWwindow *, int, int)
        glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, const int width, const int height)
        {
            WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));
            data.Width = width;
            data.Height = height;
            WindowResizeEvent event(width, height);
            data.EventCallBack(event);
        });

        glfwSetWindowIconifyCallback(m_Window, [](GLFWwindow* window, int iconified)
        {
            WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));
            if(iconified)
            {
                WindowMinimizedEvent event(true);
                data.EventCallBack(event);
                data.Minimized = true;
            }
            else
            {
                WindowMinimizedEvent event(false);
                data.EventCallBack(event);
                data.Minimized = false;
            }
        });

        glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window)
        {
            WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));
            WindowCloseEvent event;
            data.EventCallBack(event);
        });

        glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
        {
            WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));
            switch(action)
            {
                case GLFW_PRESS:
                    {
                        KeyPressedEvent event(key, 0);
                        data.EventCallBack(event);
                        // CR_CORE_INFO("{0}", event.ToString());
                        break;
                    }
                case GLFW_RELEASE:
                    {
                       KeyReleasedEvent event(key);
                       data.EventCallBack(event);
                        // CR_CORE_INFO("{0}", event.ToString());
                       break;
                    }
                case GLFW_REPEAT:
                    {
                       KeyPressedEvent event(key, 1);
                       data.EventCallBack(event);
                       break;
                    }
                default:
                    break;
            }
        });

        glfwSetCharCallback(m_Window, [](GLFWwindow* window, unsigned int keycode)
        {
            WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));

            KeyTypedEvent event(keycode);
            data.EventCallBack(event);
        });

        glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods)
        {
            WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));
            switch(action)
            {
                case GLFW_PRESS:
                    {
                        MouseButtonPressedEvent event(button);
                        data.EventCallBack(event);
                        break;
                    }
                case GLFW_RELEASE:
                    {
                        MouseButtonReleasedEvent event(button);
                        data.EventCallBack(event);
                        break;
                    }
                default:
                    break;
            }
        });

        glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xOffset, double yOffset)
        {
            WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));
            MouseScrolledEvent event(static_cast<float>(xOffset), static_cast<float>(yOffset));
            data.EventCallBack(event);
        });

        glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xPos, double yPos)
        {
            WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));
            MouseMovedEvent event(static_cast<float>(xPos), static_cast<float>(yPos));
            data.EventCallBack(event);
        });
    }

    void LinuxWindow::SetVSync(const bool enabled)
    {
        if(enabled)
            glfwSwapInterval(1);
        else
            glfwSwapInterval(0);

        m_WindowData.VSync = enabled;
    }

    bool LinuxWindow::IsVSync() const
    {
        return m_WindowData.VSync;
    }

}
