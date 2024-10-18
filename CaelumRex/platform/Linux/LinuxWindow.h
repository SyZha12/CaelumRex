#ifndef LINUXWINDOW_H
#define LINUXWINDOW_H

#include "Core/Window.h"
#include "Events/ApplicationEvent.h"
#include "Events/KeyEvent.h"
#include "Events/MouseEvent.h"

#include "OpenGL/OpenGLContext.h"
#include "Renderer/RendererContext.h"


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
        void SetEventCallBack(const EventCallBackFn& callback) override {m_WindowData.EventCallBack = callback; }
        void SetVSync(bool enabled) override;
        bool IsVSync() const override;

        void* GetNativeWindow() const { return m_Window; }
    private:
        // Not in the Window class and is used from this point
        virtual void Init(const WindowProperties& props);
        virtual void ShutDown();

        GLFWwindow* m_Window;
        RendererContext* m_Context;

        struct WindowData
        {
            std::string Title;
            unsigned int Width, Height;
            bool VSync;

            EventCallBackFn EventCallBack;
        };

        WindowData m_WindowData;
    };
}

#endif //LINUXWINDOW_H
