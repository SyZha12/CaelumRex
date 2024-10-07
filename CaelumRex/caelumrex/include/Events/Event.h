#ifndef EVENT_H
#define EVENT_H

namespace CaelumRex
{
    // Current events are blocking; meaning events are executed right away.
    // What this means is when an event occurs it immediately gets dispatched and must be dealt with.
    // Future strategy would be to use buffer events
    // TODO Create Buffer Events

    enum class EventType
    {
        None = 0,
        WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
        AppTick, AppUpdate, AppRender,
        KeyPressed, KeyReleased,
        MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
    };

    // Filter certain events
    // You don't want every event type to be logged or be present at certain points
    enum EventCategory
    {
        None = 0,
        EventCategoryApplication        = BIT(0),
        EventCategoryInput              = BIT(1),
        EventCategoryKeyboard           = BIT(2),
        EventCategoryMouse              = BIT(3),
        EventCategoryMouseButton        = BIT(4)
    };

#define EVENT_CLASS_TYPE(type) public: static EventType GetStaticType() { return EventType::type; }\
                                        virtual EventType GetEventType() const override { return GetStaticType(); }\
                                        virtual const char* GetName() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category) public: virtual int GetCategoryFlags() const override {return category; }

    class Event
    {
    public:
        bool handled = false;
        virtual EventType GetEventType() const = 0;
        virtual const char* GetName() const = 0;
        virtual int GetCategoryFlags() const = 0;
        virtual std::string ToString() const { return GetName(); }

        bool IsInCategory(EventCategory category)
        {
            return GetCategoryFlags() & category;
        }
    };

    class EventDispatcher
    {
    public:
        EventDispatcher(Event& event)
            : m_Event(event) {}

        template<typename T, typename F>
        bool Dispatch(const F& func)
        {
            if(m_Event.GetEventType() == T::GetStaticType())
            {
                m_Event.handled |= func(static_cast<T&>(m_Event));
                return true;
            }
            return false;
        }
    private:
        Event& m_Event;
    };

    // This code only works when you use the method call .ToString() with every log
    // inline std::ostream& operator<<(std::ostream& os, const Event& e)
    // {
    //     return os << e.ToString();
    // }
    // So use the following code:
    inline std::string format_as(const Event& e)
    {
        return e.ToString();
    }
}

#endif //EVENT_H
