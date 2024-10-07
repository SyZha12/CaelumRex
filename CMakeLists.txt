cmake_minimum_required(VERSION 3.28)

#====================PROJECT CAELUMREX ENGINE ===================
project(
    CaelumRex
        VERSION 0.1.0.0
        DESCRIPTION "CaelumRex Engine"
)
set(CMAKE_CXX_STANDARD 20)

#==========================SET PROPERTIES========================
#[Set default visibility to hidden for all targets]
set(CMAKE_CXX_VISIBILITY_PRESET hidden)
set(CMAKE_VISIBILITY_INLINES_HIDDEN YES)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

#[Set global cache variables]
#[Default is ON for shared library; users can overwrite this with cmake -D to choose static or shared library]
option(BUILD_SHARED_LIBS "This evaluates to true when it is a shared library" OFF)

#======================GO TO SUBDIRECTORIES======================
#[Go to subdirectories when the next CMakeLists.txt will be executed]
add_subdirectory(CaelumRex)

#[Example subdirectory]
add_subdirectory(Sandbox)

#======================LINK AND INCLUDE======================
#[Sometimes a library needs to be linked, which can be done here]
target_link_libraries(
    ${PROJECT_NAME} PRIVATE
        glfw
        GLAD::GLAD
        IMGUI::IMGUI
)

#[This subdirectory is added for including the CaelumRex.h header file; More main files could be added to this directory]
target_include_directories(
    ${PROJECT_NAME} PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/CaelumRex/caelumrex
        ${CMAKE_CURRENT_SOURCE_DIR}/CaelumRex/platform
)

#======================INCLUDE PRECOMPILED HEADER======================
#[Set precompiled header]
target_precompile_headers(
        ${PROJECT_NAME} PRIVATE
        CaelumRex/caelumrex/CRPrecompiled.h
)