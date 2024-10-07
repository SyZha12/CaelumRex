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
        CR_INFO("ExampleLayer::Update");
    }

    void OnEvent(CaelumRex::Event& event) override
    {
        CR_TRACE("{0}", event);
    }
};

class Sandbox : public CaelumRex::Application
{
public:
    Sandbox()
    {
        PushLayer(new ExampleLayer());
        PushOverlay(new CaelumRex::ImGuiLayer());
    }

    ~Sandbox()
    {

    }
};

CaelumRex::Application* CaelumRex::CreateApplication()
{
    return new Sandbox();
}
