set(FILES
        ${CMAKE_CURRENT_SOURCE_DIR}/ApplicationEvent.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Event.h
        ${CMAKE_CURRENT_SOURCE_DIR}/KeyEvent.h
        ${CMAKE_CURRENT_SOURCE_DIR}/MouseEvent.h
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