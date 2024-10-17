#include <CaelumRex.h>
#include <iostream>

class ExampleLayer : public CaelumRex::Layer
{
public:
    ExampleLayer()
        : Layer("Example")
    {

    }

    void OnUpdate() override
    {
        // CR_INFO("ExampleLayer::Update");
        if(CaelumRex::Input::IsKeyPressed(CR_KEY_RIGHT_SHIFT))
            CR_TRACE("Right shift key has been pressed!");
    }

    void OnEvent(CaelumRex::Event& event) override
    {
        // CR_TRACE("{0}", event);
    }
};

class Sandbox : public CaelumRex::Application
{
public:
    Sandbox()
    {
        // PushLayer(new ExampleLayer());
    }

    ~Sandbox()
    {

    }
};

CaelumRex::Application* CaelumRex::CreateApplication()
{
    return new Sandbox();
}
