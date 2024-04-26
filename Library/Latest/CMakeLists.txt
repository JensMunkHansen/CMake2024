return()


# TODO: Use the new FILE_SET

target_sources(
    ${linkTarget}
    PUBLIC FILE_SET
           "publicHeadersBin"
           TYPE
           HEADERS
           FILES
           ${generatedFile}
           BASE_DIRS
           ${CMAKE_CURRENT_BINARY_DIR})
