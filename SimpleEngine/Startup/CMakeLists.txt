cmake_minimum_required(VERSION 2.6)

project(Startup)

#file(GLOB_RECURSE PLATFORM_HEADERS ${CMAKE_SOURCE_DIR}/Platform/Include/*.h)

#source_group("Platform Include" FILES ${PLATFORM_HEADERS})

# set path
set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Public)
set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Private)

LIST(APPEND INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/..)

include_directories(${INCLUDE_DIR})
add_executable(${PROJECT_NAME} ${SOURCE_DIR}/win_main.cpp ${PLATFORM_HEADERS})

add_dependencies(${PROJECT_NAME} Platform)



