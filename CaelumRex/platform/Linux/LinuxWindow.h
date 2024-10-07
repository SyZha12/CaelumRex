#ifndef LINUXWINDOW_H
#define LINUXWINDOW_H

#include "Core/Window.h"
#include "Events/ApplicationEvent.h"
#include "Events/KeyEvent.h"
#include "Events/MouseEvent.h"

namespace CaelumRex
{
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

        virtual void* GetNativeWindow() const { return m_Window; }
    private:
        // Not in the Window class and is used from this point
        virtual void Init(const WindowProperties& props);
        virtual void ShutDown();

        GLFWwindow* m_Window;

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
