#ifndef SANDBOX2D_H
#define SANDBOX2D_H

#include <CaelumRex.h>

class Sandbox2D : public CaelumRex::Layer
{
public:
    Sandbox2D();

    void OnAttach() override;
    void OnDetach() override;
    void OnUpdate(CaelumRex::Timestep ts) override;
    void OnImGuiRender() override;
    void OnEvent(CaelumRex::Event& event) override;
private:
    CaelumRex::OrthographicCameraController m_CameraController;
};

#endif //SANDBOX2D_H




//=== INCLUDES ===//
// CaelumRex
// Layer
// OrthographicCameraController
// Timestep
// Event