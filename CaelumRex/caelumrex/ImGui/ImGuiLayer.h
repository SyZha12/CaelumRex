#ifndef IMGUILAYER_H
#define IMGUILAYER_H

/**
 *  @author Symen Zhang
 *  @brief Layer creation specifically for ImGui; Initializes and creates the context of ImGui.
 */

/* CaelumRex Libraries */
#include <Core/Layer.h>

namespace CaelumRex
{
    class ImGuiLayer final : public Layer
    {
    public:
        ImGuiLayer();
        ~ImGuiLayer() override = default;

        void OnAttach() override;
        void OnDetach() override;

        void Begin();
        void End();
    private:
        float m_Time = 0.0f;
    };
}

#endif //IMGUILAYER_H
