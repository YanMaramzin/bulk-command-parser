project(blockcontroller)

add_library(${PROJECT_NAME}
        ../defs/block.h
        blockcontroller.h
        blockcontroller.cpp)


target_include_directories(${PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(${PROJECT_NAME} PUBLIC iobserver)