#[Main entry point for the CaelumRex engine files (vendor/third-party will be in a different directory)]
#[PLATFORM]

set(FILES "")
set(SUBDIRECTORIES Linux OpenGL)
set(RELATIVE_PATH platform)

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
