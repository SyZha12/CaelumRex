#ifndef LINUXWINDOW_H
#define LINUXWINDOW_H

/* CaelumRex Libraries */
#include <Core/Window.h>
#include <Renderer/GraphicsContext.h>

/* Third-Party Libraries & Co*/
#include <GLFW/glfw3.h>

namespace CaelumRex
{
    // Flag if GLFW is initialized or not
    static bool s_GLFWInitialized = false;
    static void GLFWErrorCallBack(int error, const char* description) { CR_CORE_ERROR("GLFW Error ({0}): {1}", error, description); }

    class LinuxWindow : public Window
    {
    public:
        LinuxWindow(const WindowProperties& props);
        virtual ~LinuxWindow();

        void OnUpdate() override;

        unsigned int GetWidth() const override { return m_WindowData.Width; }
        unsigned int GetHeight() const override { return m_WindowData.Height; }

        // Attributes
        void SetCallBacks() const;
        void SetEventCallBack(const EventCallBackFn& callback) override { m_WindowData.EventCallBack = callback; }
        void SetVSync(bool enabled) override;
        bool IsVSync() const override;

        void* GetNativeWindow() const { return m_Window; }
    private:
        // Not in the Window class and is used from this point
        virtual void Init(const WindowProperties& props);
        virtual void ShutDown();
        void* window_iconify_callback(GLFWwindow* window, int iconified);

        GLFWwindow* m_Window;
        Scope<GraphicsContext> m_Context;

        struct WindowData
        {
            std::string Title;
            unsigned int Width, Height;
            bool VSync;
            bool Minimized;

            EventCallBackFn EventCallBack;
        };

        WindowData m_WindowData;
    };
}

#endif //LINUXWINDOW_H
