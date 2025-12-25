cmake_minimum_required(VERSION 3.31)
set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VESRION 0.0.${PATCH_VERSION})
project(bulk VERSION ${PROJECT_VESRION})

set(CMAKE_CXX_STANDARD 20)

add_executable(bulk main.cpp)

option(WITH_BOOST_TEST "Whether to build Boost test" ON)

configure_file(../version.h.in version.h)

if (MSVC)
    target_compile_options(bulk PRIVATE
            /W4
    )
    target_compile_options(bulk PRIVATE
            /W4
    )
    if(WITH_BOOST_TEST)
        target_compile_options(bulk PRIVATE
                /W4
        )
    endif()
else ()
    target_compile_options(bulk PRIVATE
            -Wall -Wextra -pedantic -Werror
    )
    target_compile_options(bulk PRIVATE
            -Wall -Wextra -pedantic -Werror
    )
    if(WITH_BOOST_TEST)
        target_compile_options(bulk PRIVATE
                -Wall -Wextra -pedantic -Werror
        )
    endif()
endif()

install(TARGETS bulk RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSsION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_PACKAGE_CONTACT example@example.com)
include(CPack)

add_subdirectory(libs)

target_link_libraries(${PROJECT_NAME} blockcontroller consolelogger filelogger)

if(WITH_BOOST_TEST)
    enable_testing()
    add_test(bulk test_version)
endif()
