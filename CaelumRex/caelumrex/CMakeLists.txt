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

#======================================================================
set(CR_SUBDIRS_CAELUMREX
        Core
        Events
        ImGui
        Renderer
        Debug
)
set(RELATIVE_PATH caelumrex)

foreach (DIR ${CR_SUBDIRS_CAELUMREX})
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