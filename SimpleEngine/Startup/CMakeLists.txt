cmake_minimum_required(VERSION 2.6)

project(Startup)

file(GLOB_RECURSE PLATFORM_HEADERS ${CMAKE_SOURCE_DIR}/Platform/Include/*.h)

source_group("Platform Include" FILES ${PLATFORM_HEADERS})

# set path
set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Include)
set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Src)

LIST(APPEND INCLUDE_DIR ${CMAKE_SOURCE_DIR}/Platform/Include)

include_directories(${INCLUDE_DIR})
add_executable(Startup ${SOURCE_DIR}/win_main.cpp ${PLATFORM_HEADERS})

link_directories(${CMAKE_BINARY_DIR}/Libs)
target_link_libraries(platform)


