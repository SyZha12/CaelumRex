#[This file will go through every header directory under the CaelumRex project]

set(FILES "")
set(SUBDIRECTORIES Linux)
set(RELATIVE_PATH "include")

#[Add all subdirectories]
foreach(VAR ${SUBDIRECTORIES})
    add_subdirectory(${VAR})
endforeach()

if(FILES)
    #[Add source files to target]
    target_sources(${PROJECT_NAME} PRIVATE ${FILES})
    #[Install source files]
    install(FILES ${FILES} DESTINATION ${RELATIVE_PATH})
endif()