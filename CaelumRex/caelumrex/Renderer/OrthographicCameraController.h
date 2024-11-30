#ifndef ORTHOGRAPHICCAMERACONTROLLER_H
#define ORTHOGRAPHICCAMERACONTROLLER_H

/* CaelumRex Libraries */
#include <Events/ApplicationEvent.h>
#include <Renderer/Camera.h>
#include <Events/MouseEvent.h>
#include <Core/Timestep.h>

namespace CaelumRex
{
    class OrthographicCameraController
    {
    public:
        OrthographicCameraController(float aspectRatio, bool rotation = false);

        void OnUpdate(Timestep ts);
        void OnEvent(Event& e);

        OrthographicCamera& GetCamera() { return m_Camera; }
        const OrthographicCamera& GetCamera() const { return m_Camera; }

        void EnableRotation(const bool enable) { m_Rotation = enable; }
    private:
        bool OnMouseScrolled(MouseScrolledEvent& e);
        bool OnWindowResized(WindowResizeEvent& e);

        float m_AspectRatio;
        float m_ZoomLevel = 1.0f;
        OrthographicCamera m_Camera;

        bool m_Rotation;
        glm::vec3 m_CameraPosition = { 0.0f, 0.0f, 0.0f };
        float m_CameraSpeed;
        float m_CameraRotation = 0.0f;
        float m_CameraRotationSpeed = 50.0f, m_CameraTranslationSpeed = 50.0f;
    };
}

#endif //ORTHOGRAPHICCAMERACONTROLLER_H
