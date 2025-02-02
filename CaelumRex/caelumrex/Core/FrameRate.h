#ifndef FRAMERATE_H
#define FRAMERATE_H

#include <Core/Timestep.h>

#include "GLFW/glfw3.h"

namespace CaelumRex
{
    class FrameRate
    {
    public:
        static Timestep GetCalculatedTimestep()
        {
            auto const time = static_cast<float>(glfwGetTime());
            Timestep const timestep = time - m_LastFrameTime;
            m_LastFrameTime = time;
            return timestep;
        }
    private:
        static float m_LastFrameTime;
    };

    float FrameRate::m_LastFrameTime;
}

#endif //FRAMERATE_H
