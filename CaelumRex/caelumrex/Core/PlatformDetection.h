#ifndef PLATFORMDETECTION_H
#define PLATFORMDETECTION_H

// Define platform that is being used with the engine
#if defined(__linux__)
        #define CR_PLATFORM_LINUX
#elif defined(_WIN64)
        #define CR_PLATFORM_WIN64
        #error "Windows (x64) is not supported"
#elif define(_WIN32)
        #define CR_PLATFORM_WIN32
        #error "Windows (x32) is not supported"
#endif

#endif //PLATFORMDETECTION_H
