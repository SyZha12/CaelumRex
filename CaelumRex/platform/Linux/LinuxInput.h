#ifndef LINUXINPUT_H
#define LINUXINPUT_H

/** CaelumRex Libraries **/
#include <Core/Input.h>

/** Third-Party Libraries & Co **/
#include <utility>


namespace CaelumRex
{
    class LinuxInput : public Input
    {
    protected:
        bool IsKeyPressedImplemented(int keycode) override;
        bool IsMouseButtonPressedImplemented(int button) override;
        std::pair<float, float> GetMousePositionImplemented() override;
        float GetMouseXImplemented() override;
        float GetMouseYImplemented() override;
    };

    Input* Input::s_Instance = new LinuxInput();
}

#endif //LINUXINPUT_H
