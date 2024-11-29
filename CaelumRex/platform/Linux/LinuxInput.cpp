/* CaelumRex Libraries */
#include <Linux/LinuxInput.h>
#include <Core/Application.h>

/* Third-Party Libraries & Co*/
#include <GLFW/glfw3.h>

namespace CaelumRex
{
    bool LinuxInput::IsKeyPressedImplemented(int keycode)
    {
        const auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
        const auto state = glfwGetKey(window , keycode);
        return state == GLFW_PRESS || state == GLFW_REPEAT;
    }

    bool LinuxInput::IsMouseButtonPressedImplemented(int button)
    {
        const auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
        const auto state = glfwGetMouseButton(window , button);
        return state == GLFW_PRESS;
    }

    std::pair<float, float> LinuxInput::GetMousePositionImplemented()
    {
        const auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);

        return { static_cast<float>(xpos), static_cast<float>(ypos) };
    }

    float LinuxInput::GetMouseYImplemented()
    {
        auto[x, y] = GetMousePositionImplemented();
        return x;
    }

    float LinuxInput::GetMouseXImplemented()
    {
        auto[x, y] = GetMousePositionImplemented();
        return y;
    }
}
