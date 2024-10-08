#ifndef IMGUILAYER_H
#define IMGUILAYER_H

#include "Core/Layer.h"
// #include "imgui.h"

#include "OpenGL/imgui_impl_opengl3.h"

#include "Core/Application.h"

namespace CaelumRex
{
    class CAELUMREX_EXPORT ImGuiLayer : public Layer
    {
    public:
        ImGuiLayer();
        ~ImGuiLayer();

        void OnAttach();
        void OnDetach();
        void OnUpdate();
        void OnEvent(Event& event);
    private:
        float m_Time = 0.0f;

        Application* s_instance;
    };
}

#endif //IMGUILAYER_H
