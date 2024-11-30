#[Main entry point for the CaelumRex engine files (vendor/third-party will be in a different directory)]
#[PLATFORM]

set(CR_SUBDIRS_PLATFORM
        Linux
        OpenGL
)
set(RELATIVE_PATH platform)

foreach (DIR ${CR_SUBDIRS_PLATFORM})
    file(GLOB CR_FILES CONFIGURE_DEPENDS "${DIR}/*.cpp" "${DIR}/*.h")

    if(CR_FILES)
        target_sources(${PROJECT_NAME} PRIVATE ${CR_FILES})
        install(FILES ${CR_FILES} DESTINATION ${RELATIVE_PATH})
    endif ()

    target_include_directories(
            ${PROJECT_NAME} PUBLIC
            $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/${DIR}>
            $<INSTALL_INTERFACE:${DIR}>
    )
endforeach ()