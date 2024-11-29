#ifndef CORE_H
#define CORE_H

#include <csignal>

//====================== DEFINITIONS ======================//
// Bind for Application functions
#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)
#define BIND_EVENTS(x) [this](auto&& _PH) { x(std::forward<decltype(_PH)>(_PH)); }
#define BIND_EVENTS_DISPATCH(x) [this](auto&& _PH) { return x(std::forward<decltype(_PH)>(_PH)); }
#define CR_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)
#define BIT(x) (1 << x)

#define EMBED_BREAKPOINT raise(SIGABRT)

#ifdef CR_ENABLE_ASSERTS
    #define CR_ASSERT(x, ...) {if(!(x)) {CR_ERROR("Assertion Failed: {0}", __VA_ARGS__); EMBED_BREAKPOINT;}}
    #define CR_CORE_ASSERT(x, ...) {if(!(x)) {CR_CORE_ERROR("Assertion Failed: ", __VA_ARGS__); EMBED_BREAKPOINT;}}
#else
    #define CR_ASSERT(x, ...)
    #define CR_CORE_ASSERT(x, ...)
#endif



#include <memory>
namespace CaelumRex
{
    template<typename T>
    using Scope = std::unique_ptr<T>;
    template<typename T, typename ... Args>
    constexpr Scope<T> CreateScope(Args&& ... args)
    {
        return std::make_unique<T>(std::forward<Args>(args)...);
    }

    template<typename T>
    using Ref = std::shared_ptr<T>;
    template<typename T, typename ... Args>
    constexpr Ref<T> CreateRef(Args&& ... args)
    {
        return std::make_shared<T>(std::forward<Args>(args)...);
    }

}

#endif //CORE_H
