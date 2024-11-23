#ifndef IMGUILAYER_H
#define IMGUILAYER_H

#include "Core/Layer.h"

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
