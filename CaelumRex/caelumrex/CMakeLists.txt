#[Main entry point for the CaelumRex engine files (vendor/third-party will be in a different directory)]
#[CAELUMREX]

#[This code is used for the include and src directories of the CaelumRex files]
target_include_directories(
    ${PROJECT_NAME} PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
)

#[Creates an export file to (un)hide certain code from outside the project]
#[This is generated under the caelumrex directory for the project itself]
include(GenerateExportHeader)
generate_export_header(${PROJECT_NAME})
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/caelumrex_export.h DESTINATION include)

set(FILES "")
set(SUBDIRECTORIES Core Events ImGui Renderer Debug)
set(RELATIVE_PATH caelumrex)

#[Add all subdirectories]
foreach(VAR ${SUBDIRECTORIES})
    target_include_directories(
            ${PROJECT_NAME} PUBLIC
            $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/${VAR}>
            $<INSTALL_INTERFACE:${VAR}>
    )
    add_subdirectory(${VAR})
endforeach()

if(FILES)
    #[Add source files to target]
    target_sources(${PROJECT_NAME} PRIVATE ${FILES})
    #[Install source files]
    install(FILES ${FILES} DESTINATION ${RELATIVE_PATH})
endif()
