add_executable(
    Sandbox
        SandboxApplication.cpp
)

target_link_libraries(
    Sandbox PRIVATE
        CaelumRex::CaelumRex
)
