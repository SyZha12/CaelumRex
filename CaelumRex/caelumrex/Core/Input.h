#ifndef INPUT_H
#define INPUT_H

/**
 *  @author Symen Zhang
 *  @brief Base input class
 */

/** Third-Party Libraries & Co **/
#include <utility>

namespace CaelumRex
{
    class Input
    {
    public:
        virtual ~Input() = default;

        static bool IsKeyPressed(const int keycode) { return s_Instance->IsKeyPressedImplemented(keycode); }
        static bool IsMouseButtonPressed(const int button) { return s_Instance->IsMouseButtonPressedImplemented(button); }

        static std::pair<float, float> GetMousePosition() { return s_Instance->GetMousePositionImplemented(); }
        static float GetMouseX() { return s_Instance->GetMouseXImplemented(); }
        static float GetMouseY() { return s_Instance->GetMouseYImplemented(); }

    protected:
        virtual bool IsKeyPressedImplemented(int keycode) = 0;
        virtual bool IsMouseButtonPressedImplemented(int button) = 0;
        virtual std::pair<float, float> GetMousePositionImplemented() = 0;
        virtual float GetMouseXImplemented() = 0;
        virtual float GetMouseYImplemented() = 0;

    private:
        static Input* s_Instance;
    };
}
#endif //INPUT_H
