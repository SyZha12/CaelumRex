add_executable(
    Sandbox3D
        SandboxApplication.cpp
)

target_link_libraries(
    Sandbox3D PRIVATE
        CaelumRex::CaelumRex
)
