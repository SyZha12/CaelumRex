#ifndef APPLICATION_H
#define APPLICATION_H

#include "caelumrex_export.h"

namespace CaelumRex
{
    class CAELUMREX_EXPORT Application
    {
        public:
            Application();
            virtual ~Application();

            void Run();
    };

    Application* CreateApplication();
}

#endif //APPLICATION_H
