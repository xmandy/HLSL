cmake_minimum_required(VERSION 2.6)

# solution
project(Engine)
add_definitions(-DUNICODE -D_UNICODE)

set(CMAKE_BUILD_TYPE Release CACHE STRING "aaa" FORCE)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Libs)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Libs)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Libs)

message(STATUS "BuildType: " ${CMAKE_BUILD_TYPE})
message(STATUS "MSVC_VERSION: " ${MSVC_VERSION})

# Use this to enable c++17
if (MSVC_VERSION GREATER_EQUAL "1900")
    include(CheckCXXCompilerFlag)
    CHECK_CXX_COMPILER_FLAG("/std:c++latest" _cpp_latest_flag_supported)
    if (_cpp_latest_flag_supported)
        add_compile_options("/std:c++latest")
    endif()
endif()

add_subdirectory(Common)

add_subdirectory(Components)

add_subdirectory(Platform)

add_subdirectory(Render)

add_subdirectory(Game)

# the application project always in the end
add_subdirectory(Startup)