project(blockcontroller)

add_library(${PROJECT_NAME}
        ../defs/block.h
        blockcontroller.h
        blockcontroller.cpp)


target_include_directories(${PROJECT_NAME} PUBLIC
        .
)

target_link_libraries(${PROJECT_NAME} PUBLIC iobserver)