add_executable(
    Example
        SandboxApplication.cpp
)

target_link_libraries(
    Example PRIVATE
        CaelumRex::CaelumRex
)