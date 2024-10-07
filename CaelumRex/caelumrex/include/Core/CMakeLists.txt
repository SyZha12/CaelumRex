set(FILES
        ${CMAKE_CURRENT_SOURCE_DIR}/Application.h
        ${CMAKE_CURRENT_SOURCE_DIR}/EntryApplication.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Log.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Core.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Window.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Layer.h
        ${CMAKE_CURRENT_SOURCE_DIR}/LayerStack.h
)
set(SUBDIRECTORIES "")
set(RELATIVE_PATH "include")

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