#[Main entry point for the CaelumRex engine files (vendor/third-party will be in a different directory)]

#======================CREATE LIBRARY===================
#[Create an initial library with zero parameters]
add_library(${PROJECT_NAME} ""
        CaelumRex.h
        include/Core/EntryApplication.h
)
#[Give the library the alias CaelumRex::CaelumRex for the target_link_libraries]
add_library(CaelumRex::CaelumRex ALIAS ${PROJECT_NAME})

#[This code is used for the include and src directories of the CaelumRex files]
target_include_directories(
    ${PROJECT_NAME} PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
        $<INSTALL_INTERFACE:include>
)

if(BUILD_SHARED_LIBS)
    set(STATIC_POSTFIX "-s")
    set_target_properties(
        ${PROJECT_NAME} PROPERTIES
            COMPILE_FLAGS -DFOO_STATIC_DEFINE
    )
endif()

#[Rename target]
set_target_properties(
    ${PROJECT_NAME} PROPERTIES
        DEBUG_POSTFIX "${STATIC_POSTFIX}-d"
        RELEASE_POSTFIX "${STATIC_POSTFIX}"
        MINSIZEREL_POSTFIX "${STATIC_POSTFIX}-mr"
        RELWITHDEBINFO "${STATIC_POSTFIX}-rd"
)

#[Creates an export file to (un)hide certain code from outside the project]
include(GenerateExportHeader)
generate_export_header(${PROJECT_NAME})
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/caelumrex_export.h DESTINATION include)

#======================GO TO SUBDIRECTORIES======================
#[Go to subdirectories when the next CMakeLists.txt will be executed]
add_subdirectory(include)
add_subdirectory(src)
