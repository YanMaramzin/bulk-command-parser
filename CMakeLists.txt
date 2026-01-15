cmake_minimum_required(VERSION 3.28)

project(async
        VERSION 1.0.0
        LANGUAGES CXX
)

# ------------------------
# Общие настройки
# ------------------------
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)  # важно для shared

include(GNUInstallDirs)

# ------------------------
# Библиотека async
# ------------------------
add_library(async SHARED
        libs/async/src/async.cpp
        libs/blockcontroller/src/blockcontroller.cpp
        libs/consolelogger/src/consoleworker.cpp
        libs/filelogger/src/fileworker.cpp
        libs/filelogger/src/filelogger.cpp
        libs/dispatcher/src/dispatcher.cpp
)

target_include_directories(async
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/libs/async/include>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/libs/blockcontroller/include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/libs/consolelogger/include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/libs/filelogger/include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/libs/dispatcher/include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/libs/common/include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/libs/defs/include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/libs/sinks/include>
)

target_link_libraries(async
        PRIVATE pthread
)

set_target_properties(async PROPERTIES
        OUTPUT_NAME async
        VERSION ${PROJECT_VERSION}
        SOVERSION 1
)

# ------------------------
# Исполняемый файл (демо)
# ------------------------
add_executable(async_cli
        main.cpp
)

target_link_libraries(async_cli
        PRIVATE async
)

# ------------------------
# Установка
# ------------------------
install(TARGETS async async_cli
        EXPORT asyncTargets
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

install(DIRECTORY libs/async/include/
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(EXPORT asyncTargets
        FILE asyncTargets.cmake
        NAMESPACE async::
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/async
)

# ------------------------
# bulk_server
# ------------------------
find_package(Boost REQUIRED COMPONENTS system)

add_executable(bulk_server
        bulk_server/src/main.cpp
        bulk_server/src/server.cpp
        bulk_server/src/session.cpp
)
target_include_directories(bulk_server PRIVATE
        bulk_server/include
        include
        ${CMAKE_CURRENT_SOURCE_DIR}/libs/async/include
)
target_link_libraries(bulk_server PRIVATE async ${Boost_LIBRARIES} pthread)