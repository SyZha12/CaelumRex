#ifndef CORE_H
#define CORE_H

#define BIT(x) (1 << x)

#ifdef CR_ENABLE_ASSERTS
    #define CR_ASSERT(x, ...) {if(!(x)) {CR_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak();}}
    #define CR_CORE_ASSERT(x, ...) {if(!(x)) {CR_CORE_ERROR("Assertion Failed: ", __VA_ARGS__); __debugbreak();}}
#else
    #define CR_ASSERT(x, ...)
    #define CR_CORE_ASSERT(x, ...)
#endif

#endif //CORE_H
