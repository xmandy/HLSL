cmake_minimum_required(VERSION 2.6)

# solution
project(Engine)
add_definitions(-DUNICODE -D_UNICODE)

set(CMAKE_BUILD_TYPE Release CACHE STRING "aaa" FORCE)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Libs)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Libs)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Libs)

message(STATUS "11" ${CMAKE_BUILD_TYPE})


add_subdirectory(Render)

add_subdirectory(Platform)

# the application project always in the end
add_subdirectory(Startup)