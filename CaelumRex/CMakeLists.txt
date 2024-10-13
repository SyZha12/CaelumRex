#[Main entry point for the CaelumRex engine files (vendor/third-party will be in a different directory)]
#[CAELUMREX]

#======================CREATE LIBRARY===================
#[Create an initial library with zero parameters]
add_library(${PROJECT_NAME} ""
        caelumrex/Core/KeyCodes.h)
#[Give the library the alias CaelumRex::CaelumRex for the target_link_libraries]
add_library(CaelumRex::CaelumRex ALIAS ${PROJECT_NAME})

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

#======================GO TO SUBDIRECTORIES======================
#[Go to subdirectories when the next CMakeLists.txt will be executed]
add_subdirectory(caelumrex)
add_subdirectory(platform)
add_subdirectory(vendor)