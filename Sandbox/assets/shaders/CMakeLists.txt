file(GLOB MY_FILES "*.glsl")

foreach (FILE ${MY_FILES})
    get_filename_component(FILE_NAME ${FILE} NAME)
    file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/${FILE_NAME}
            DESTINATION ${CMAKE_CURRENT_BINARY_DIR}
    )
endforeach ()