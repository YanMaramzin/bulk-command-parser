add_library(defs INTERFACE
        block.h)

target_include_directories(defs
        INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}
)