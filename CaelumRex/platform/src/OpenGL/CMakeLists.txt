#[This file will go through every header directory under the CaelumRex project]

set(FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/imgui_impl_opengl3.cpp
)
set(SUBDIRECTORIES "")
set(RELATIVE_PATH "src")

#[Add all subdirectories]
foreach(VAR ${SUBDIRECTORIES})
    add_subdirectory(${VAR})
endforeach()

if(FILES)
    #[Add source files to target]
    target_sources(${PROJECT_NAME} PRIVATE ${FILES})
    #[Install source files]
    install(FILES ${FILES} DESTINATION ${RELATIVE_PATH})
endif()
