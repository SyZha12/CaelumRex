set(FILES
        ${CMAKE_CURRENT_SOURCE_DIR}/ImGuiLayer.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/ImGuiLayer.h
)
set(SUBDIRECTORIES "")
set(RELATIVE_PATH caelumrex)

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