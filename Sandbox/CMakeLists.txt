add_executable(
    Sandbox
        SandboxApplication.cpp
        Sandbox2D.cpp
)

target_link_libraries(
    Sandbox PRIVATE
        CaelumRex::CaelumRex
)
