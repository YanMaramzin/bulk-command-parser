project(filelogger)

add_library(${PROJECT_NAME}
        filelogger.h
        filelogger.cpp
)

target_include_directories(${PROJECT_NAME} PUBLIC
        .
)

target_link_libraries(${PROJECT_NAME} PUBLIC iobserver)