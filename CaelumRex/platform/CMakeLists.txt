#[Main entry point for the CaelumRex engine files (vendor/third-party will be in a different directory)]
#[PLATFORM]

#[This code is used for the include and src directories of the CaelumRex files]
target_include_directories(
    ${PROJECT_NAME} PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
        $<INSTALL_INTERFACE:include>
)

#======================GO TO SUBDIRECTORIES======================
#[Go to subdirectories when the next CMakeLists.txt will be executed]
add_subdirectory(include)
add_subdirectory(src)
