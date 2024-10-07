set(FILES
        ${CMAKE_CURRENT_SOURCE_DIR}/Application.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Log.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Layer.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/LayerStack.cpp
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