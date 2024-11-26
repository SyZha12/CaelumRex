#ifndef CORE_H
#define CORE_H

//====================== DEFINITIONS ======================//
// Bind for Application functions
#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

// #define CR_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

#define BIT(x) (1 << x)

#if __SIZEOF_POINTER__ > 4
#define EMBED_BREAKPOINT_PTR ".quad"
#else
#define EMBED_BREAKPOINT_PTR ".long"
#endif

// TODO In Core.h; how to set breakpoint during debugging?
#define EMBED_BREAKPOINT \
asm("0:"                              \
".pushsection embed-breakpoints;" \
EMBED_BREAKPOINT_PTR " 0b;"       \
".popsection;")

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

    template<typename T>
    using Ref = std::shared_ptr<T>;

}

#endif //CORE_H
