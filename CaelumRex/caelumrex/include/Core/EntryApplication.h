#ifndef ENTRYAPPLICATION_H
#define ENTRYAPPLICATION_H

extern CaelumRex::Application* CaelumRex::CreateApplication();

int main(int argc, char ** argv)
{
    auto* application = CaelumRex::CreateApplication();
    application->Run();
    delete application;
}

#endif //ENTRYAPPLICATION_H
