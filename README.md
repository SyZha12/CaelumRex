# CaelumRex
## CaelumRex Engine Introduction
The CaelumRex engine is first and foremost a fun experience/project where I learn all kinds of new things during my coding journey.
It provides insights into the C++ programming language, and uses different kinds of APIs and libraries.

My focus here is creating a game engine from scratch using OpenGL as the graphics API where I will learn to render all kinds of stuff.
First I have to create a window; GLFW will be used during this time, because of its simplicity, but might convert to SDL3 in the future.

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
