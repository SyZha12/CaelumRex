#ifndef IMGUILAYER_H
#define IMGUILAYER_H

// #include "CRPrecompiled.h"
#include "Core/Layer.h"
// #include "Core/LayerStack.h"
// #include "Core/Application.h"
// #include "imgui-docking/imgui.h"
// #include "imgui-docking/backends/imgui_impl_glfw.h"
// #include "imgui-docking/backends/imgui_impl_opengl3.h"


namespace CaelumRex
{
    class ImGuiLayer final : public Layer
    {
    public:
        ImGuiLayer();
        ~ImGuiLayer() override = default;

        void OnAttach() override;
        void OnDetach() override;
        void OnImGuiRender() override;

        void Begin();
        void End();
    private:
        float m_Time = 0.0f;
    };
}

#endif //IMGUILAYER_H
