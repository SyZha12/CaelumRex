#[Main entry point for the CaelumRex engine files (vendor/third-party will be in a different directory)]
#[CAELUMREX]

#[This code is used for the include and src directories of the CaelumRex files]
target_include_directories(
    ${PROJECT_NAME} PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
        $<INSTALL_INTERFACE:include>
)

#[Creates an export file to (un)hide certain code from outside the project]
include(GenerateExportHeader)
generate_export_header(${PROJECT_NAME})
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/caelumrex_export.h DESTINATION include)

#======================GO TO SUBDIRECTORIES======================
#[Go to subdirectories when the next CMakeLists.txt will be executed]
add_subdirectory(include)
add_subdirectory(src)
