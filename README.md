# CaelumRex
## CaelumRex Engine Introduction
The CaelumRex engine is first and foremost a fun experience/project where I learn all kinds of new things during my coding journey.
It provides insights into the C++ programming language, and uses different kinds of APIs and libraries.

My focus here is creating a game engine from scratch using OpenGL as the graphics API where I will learn to render all kinds of stuff.
First I have to create a window; GLFW will be used during this time, because of its simplicity, but might convert to SDL3 in the future.
This engine is built up with an example of a series from TheCherno (https://www.youtube.com/playlist?list=PLlrATfBNZ98dC-V-N3m0Go4deliWHPFwT)
where I learn how a game engine could be designed.
I will try to add my own ideas into this, so it's not a complete copy/paste project, but will use lots of implementation ideas from his project.

## What am I learning?
### Programming Languages and Libraries/APIs
1. C++
2. GLFW
3. OpenGL
4. GLAD
5. spdlog
6. imgui

### IDE
- CLion

### Build Tool
- CMake

## How To Use?
1. Use the terminal in the project directory
2. Use 'git submodule add <URL_CaelumRex> <DIRECTORY>' to add the repository you the project
3. In the top CMakeLists.txt file; 'add_subdirectory(ROOT_PATH_OF_ENGINE)' and 'target_link_libraries(PROJECT PUBLIC CaelumRex::CaelumRex)'
4. Add in your file(s) '#include <CaelumRex.h>'

## Starting Point
As a note to myself; start by going to the application.h and .cpp file as this is the starting class of the engine. The application class
will be used as the base class (inherited) for the external project:   class Sandbox : public Application.

As most are used to the int main() function; this is called in the engine (EntryApplication.h file) and will be only handled by the engine.
Basically, this is still the main starting point of the program and to describe this:
1. Include the "CaelumRex.h" header file to the project.
2. This header file includes the "EntryApplication.h" file with the main() function.
3. Executing starts with an extern function CreateApplication().
4. The inherited function in the "Sandbox/Application" class in the external project instantiates a new class object and executes the code thereafter.


