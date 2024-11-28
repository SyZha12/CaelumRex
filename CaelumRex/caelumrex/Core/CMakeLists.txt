set(FILES
        ${CMAKE_CURRENT_SOURCE_DIR}/Application.h
        ${CMAKE_CURRENT_SOURCE_DIR}/EntryApplication.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Log.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Core.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Window.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Window.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Layer.h
        ${CMAKE_CURRENT_SOURCE_DIR}/LayerStack.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Application.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Log.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Layer.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/LayerStack.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Input.h
        ${CMAKE_CURRENT_SOURCE_DIR}/KeyCodes.h
        ${CMAKE_CURRENT_SOURCE_DIR}/MouseButtonCodes.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Timestep.h
        ${CMAKE_CURRENT_SOURCE_DIR}/PlatformDetection.h
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