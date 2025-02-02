#ifndef ENGINEEVENT_H
#define ENGINEEVENT_H
#include "Event.h"
#include <Events/ApplicationEvent.h>

#include "Renderer.h"

namespace CaelumRex
{
    class EngineEvent
    {
        void RunEvents(Event& e)
        {
            // EventDispatcher is used to determine when certain events occur like WindowCloseEvent
            EventDispatcher dispatcher(e);
            dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENTS_DISPATCH(OnWindowClose));
            dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENTS_DISPATCH(OnWindowResize));
            dispatcher.Dispatch<WindowMinimizedEvent>(BIND_EVENTS_DISPATCH(OnWindowMinimized));
        }

        bool OnWindowClose(WindowCloseEvent& e)
        {
            m_Running = false;
            return true;
        }

        bool OnWindowResize(const WindowResizeEvent& e)
        {
            Renderer::OnWindowResize(e.GetWidth(), e.GetHeight());

            return false;
        }

        bool OnWindowMinimized(const WindowMinimizedEvent& e)
        {
            if(e.IsMinimized())
            {
                m_Minimized = true;
                return true;
            }
            m_Minimized = false;

            return false;
        }
    };
}

#endif //ENGINEEVENT_H
