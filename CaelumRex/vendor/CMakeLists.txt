add_subdirectory(spdlog)
add_subdirectory(glfw)
add_subdirectory(glad)
#add_subdirectory(imgui)
add_subdirectory(imgui-docking/imgui-docking)
add_subdirectory(glm)
add_subdirectory(stb_image)

find_package(Git QUIET)
if(GIT_FOUND AND EXISTS "${PROJECT_SOURCE_DIR}/.git")
    # Update submodules as needed
    option(GIT_SUBMODULE "Check submodules during build" ON)
    if(GIT_SUBMODULE)
        message(STATUS "Submodule update")
        execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive
                WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                RESULT_VARIABLE GIT_SUBMOD_RESULT)
        if(NOT GIT_SUBMOD_RESULT EQUAL "0")
            message(FATAL_ERROR "git submodule update --init --recursive failed with ${GIT_SUBMOD_RESULT}, please checkout submodules")
        endif()
    endif()
endif()

if(NOT EXISTS "${PROJECT_SOURCE_DIR}/CaelumRex/vendor/glfw/CMakeLists.txt")
    message(FATAL_ERROR "The submodules were not downloaded! GIT_SUBMODULE was turned off or failed. Please update submodules and try again.")
endif()

if(NOT EXISTS "${PROJECT_SOURCE_DIR}/CaelumRex/vendor/spdlog/CMakeLists.txt")
    message(FATAL_ERROR "The submodules were not downloaded! GIT_SUBMODULE was turned off or failed. Please update submodules and try again.")
endif()

#if(NOT EXISTS "${PROJECT_SOURCE_DIR}/CaelumRex/vendor/imgui/CMakeLists.txt")
#    message(FATAL_ERROR "The submodules were not downloaded! GIT_SUBMODULE was turned off or failed. Please update submodules and try again.")
#endif()

if(NOT EXISTS "${PROJECT_SOURCE_DIR}/CaelumRex/vendor/imgui-docking/imgui-docking/CMakeLists.txt")
    message(FATAL_ERROR "The submodules were not downloaded! GIT_SUBMODULE was turned off or failed. Please update submodules and try again.")
endif()

if(NOT EXISTS "${PROJECT_SOURCE_DIR}/CaelumRex/vendor/glm/CMakeLists.txt")
    message(FATAL_ERROR "The submodules were not downloaded! GIT_SUBMODULE was turned off or failed. Please update submodules and try again.")
endif()

#[This subdirectory is added for including the CaelumRex.h header file; More main files could be added to this directory]
target_include_directories(
        ${PROJECT_NAME} PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/spdlog/include
        ${CMAKE_CURRENT_SOURCE_DIR}/glfw/include
        ${CMAKE_CURRENT_SOURCE_DIR}/glad/include
#        ${CMAKE_CURRENT_SOURCE_DIR}/imgui
        ${CMAKE_CURRENT_SOURCE_DIR}/imgui-docking
        ${CMAKE_CURRENT_SOURCE_DIR}/glm/
        ${CMAKE_CURRENT_SOURCE_DIR}/stb_image/
)
