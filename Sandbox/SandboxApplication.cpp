#include <CaelumRex.h>
#include <iostream>

class Sandbox : public CaelumRex::Application
{
public:
    Sandbox()
    {

    }

    ~Sandbox()
    {

    }
};

CaelumRex::Application* CaelumRex::CreateApplication()
{
    return new Sandbox();
}
