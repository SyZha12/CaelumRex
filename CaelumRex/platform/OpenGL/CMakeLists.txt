set(FILES
        ${CMAKE_CURRENT_SOURCE_DIR}/OpenGLContext.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/OpenGLContext.h
        ${CMAKE_CURRENT_SOURCE_DIR}/OpenGLBuffer.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/OpenGLBuffer.h
        ${CMAKE_CURRENT_SOURCE_DIR}/OpenGLVertexArray.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/OpenGLVertexArray.h
        ${CMAKE_CURRENT_SOURCE_DIR}/OpenGLRendererAPI.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/OpenGLRendererAPI.h
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