set(FILES
        ${CMAKE_CURRENT_SOURCE_DIR}/imgui_impl_opengl3.h
        ${CMAKE_CURRENT_SOURCE_DIR}/imgui_impl_opengl3.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/imgui_impl_opengl3_loader.h
        ${CMAKE_CURRENT_SOURCE_DIR}/imgui_impl_glfw.h
        ${CMAKE_CURRENT_SOURCE_DIR}/imgui_impl_glfw.cpp
)
set(SUBDIRECTORIES "")
set(RELATIVE_PATH platform)

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