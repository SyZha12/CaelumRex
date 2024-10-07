#[Main entry point for the CaelumRex engine files (vendor/third-party will be in a different directory)]
#[CAELUMREX]
cmake_minimum_required(VERSION 3.28)
project(glad)

add_library(${PROJECT_NAME} "")
#[Give the library the alias CaelumRex::CaelumRex for the target_link_libraries]
add_library(GLAD::GLAD ALIAS ${PROJECT_NAME})

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
