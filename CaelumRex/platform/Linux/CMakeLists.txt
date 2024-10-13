set(FILES
        ${CMAKE_CURRENT_SOURCE_DIR}/LinuxWindow.h
        ${CMAKE_CURRENT_SOURCE_DIR}/LinuxWindow.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/LinuxInput.h
        ${CMAKE_CURRENT_SOURCE_DIR}/LinuxInput.cpp
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