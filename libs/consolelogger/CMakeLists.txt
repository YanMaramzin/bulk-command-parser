project(consolelogger)

add_library(${PROJECT_NAME}
        consolelogger.h
        consolelogger.cpp
)

target_include_directories(${PROJECT_NAME} PUBLIC
        .
)

target_link_libraries(${PROJECT_NAME} PUBLIC iobserver)