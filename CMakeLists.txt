cmake_minimum_required(VERSION 3.31)
project(refined VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

set(CMAKE_VERBOSE_MAKEFILE ON)

add_library(refined INTERFACE)

target_include_directories(refined INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

install(DIRECTORY include/
    DESTINATION include
)

install(TARGETS refined
    EXPORT refinedConfig
)

install(EXPORT refinedConfig
    FILE refinedConfig.cmake
    NAMESPACE refined::
    DESTINATION lib/cmake/refined
)

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
  ${CMAKE_CURRENT_BINARY_DIR}/refined-version.cmake
  VERSION "${PROJECT_VERSION}"
  COMPATIBILITY SameMajorVersion
)

install(FILES ${CMAKE_CURRENT_BINARY_DIR}/refined-version.cmake
        DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/refined"
)

include(FetchContent)
FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG v3.8.0
)
FetchContent_MakeAvailable(Catch2)
set(Catch2_LIBRARIES Catch2::Catch2WithMain)

# Tests
enable_testing()
add_executable(tests test/test.cpp)

target_link_libraries(tests PRIVATE Catch2::Catch2WithMain)
target_link_libraries(tests PRIVATE refined)

include(CTest)
include(Catch)
catch_discover_tests(tests)