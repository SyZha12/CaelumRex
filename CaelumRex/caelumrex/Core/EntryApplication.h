#ifndef ENTRYAPPLICATION_H
#define ENTRYAPPLICATION_H

// By using this header; main entry point stays separate from the other applications that use this engine
// Thus, main starts executing from here
// extern CaelumRex::Application* CaelumRex::CreateApplication();

int main(int argc, char ** argv)
{
    // Initialise log of the core application
    CaelumRex::Log::Init();
    CR_CORE_INFO("Core logger initialized");
    CR_INFO("Client logger initialized");

    // STEP 1: Instantiate the application class
    // By creating the starting class in the client application and returning a pointer; the engine will take care of starting up the whole system
    auto* application = CaelumRex::CreateApplication();
    application->Run();
    delete application;
}

#endif //ENTRYAPPLICATION_H
