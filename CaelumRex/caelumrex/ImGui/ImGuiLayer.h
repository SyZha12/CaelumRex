#ifndef IMGUILAYER_H
#define IMGUILAYER_H

#include "Core/Layer.h"
#include "imgui.h"

#include "Events/MouseEvent.h"
#include "Events/ApplicationEvent.h"
#include "Events/KeyEvent.h"
#include "OpenGL/imgui_impl_opengl3.h"
#include "OpenGL/imgui_impl_glfw.h"
#include "Linux/LinuxWindow.h"

#include "Core/Application.h"

namespace CaelumRex
{
    class CAELUMREX_EXPORT ImGuiLayer : public Layer
    {
    public:
        ImGuiLayer();
        ~ImGuiLayer() override;

        void OnAttach() override;
        void OnDetach() override;
        void OnUpdate() override;
        void OnEvent(Event& event) override;
    private:
        bool OnMouseButtonPressedEvent(MouseButtonPressedEvent& e);
        bool OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e);
        bool OnMouseMovedEvent(MouseMovedEvent& e);
        bool OnMouseScrolledEvent(MouseScrolledEvent& e);
        bool OnKeyPressedEvent(KeyPressedEvent& e);
        bool OnKeyReleasedEvent(KeyReleasedEvent& e);
        bool OnKeyTypedEvent(KeyTypedEvent& e);
        bool OnWindowResizeEvent(WindowResizeEvent& e);
        float m_Time = 0.0f;

        Application* s_instance;
    };
}

#endif //IMGUILAYER_H
