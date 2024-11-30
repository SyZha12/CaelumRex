cmake_minimum_required(VERSION 3.28)

set(SUBDIRECTORIES
        assets/shaders
        assets/textures
)

foreach (SUBDIR ${SUBDIRECTORIES})
    set(DIR ${SUBDIR})
    add_subdirectory(${SUBDIR})
endforeach ()

add_executable(
    Sandbox2D
        SandboxApplication.cpp
        Sandbox2D.cpp
)

target_link_libraries(
        Sandbox2D PRIVATE
        CaelumRex::CaelumRex
)