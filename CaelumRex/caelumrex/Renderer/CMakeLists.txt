set(FILES
        ${CMAKE_CURRENT_SOURCE_DIR}/RendererContext.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Shader.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Shader.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Buffer.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Buffer.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Renderer.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Renderer.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/VertexArray.h
        ${CMAKE_CURRENT_SOURCE_DIR}/VertexArray.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/RendererAPI.h
        ${CMAKE_CURRENT_SOURCE_DIR}/RendererAPI.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/RenderCommand.h
        ${CMAKE_CURRENT_SOURCE_DIR}/RenderCommand.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Camera.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Camera.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Texture.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Texture.cpp
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