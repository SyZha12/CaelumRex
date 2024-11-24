#ifndef WINDOW_H
#define WINDOW_H

#include "Events/Event.h"
#include "Core/Log.h"

namespace CaelumRex
{
    // Used for each created window with their own properties
    // Used with Window::Create()
    struct WindowProperties
    {
        std::string Title;
        unsigned int Width, Height;

        // Struct callable
        WindowProperties(
            const std::string& title = "CaelumRex",
            unsigned int width = 1920,
            unsigned int height = 1080
        )
            : Title(title)
            , Width(width)
            , Height(height)
        {}
    };

    // Interface that represents a desktop system based window
    class Window
    {
    public:
        // Used to instantiate a new window; window is created from this class
        static Window* Create(const WindowProperties& props = WindowProperties());

        // Type alias to a function with the Event class as parameter with no return type
        // Is used in the SetEventCallBack function
        using EventCallBackFn = std::function<void(Event&)>;

        // default means use the compiler-generated version of this function (= delete means don't generate this function automatically)
        virtual ~Window() = default;

        // = 0 syntax declares a pure virtual function
        virtual void OnUpdate() = 0;

        virtual unsigned int GetWidth() const = 0;
        virtual unsigned int GetHeight() const = 0;

        // Attributes
        virtual void SetEventCallBack(const EventCallBackFn& callback) = 0;
        virtual void SetVSync(bool enabled) = 0;
        virtual bool IsVSync() const = 0;

        virtual void* GetNativeWindow() const = 0;
    };
}

#endif //WINDOW_H
