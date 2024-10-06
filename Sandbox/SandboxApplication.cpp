#include <CaelumRex.h>
#include <iostream>

class Sandbox : public CaelumRex::Application
{
public:
    Sandbox()
    {
        std::cout << "It works!";
    }

    ~Sandbox()
    {

    }
};

CaelumRex::Application* CaelumRex::CreateApplication()
{
    return new Sandbox();
}
