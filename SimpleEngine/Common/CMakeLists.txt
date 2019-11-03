cmake_minimum_required(VERSION 2.6)

project(Common)
set(TARGET_NAME ${PROJECT_NAME})
add_library(${TARGET_NAME})

# begin use cmake 3.0 feature
# set path
set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Public)
set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Private)

file(GLOB_RECURSE INCLUDE_FILES ${INCLUDE_DIR}/*.h)
file(GLOB_RECURSE SRC_FILES ${SOURCE_DIR}/*.cpp)

# for finegrained controll, add file one by one
#set(INCLUDE_FILES ${INCLUDE_DIR}/Win32Window.h
#)
#set(SRC_FILES ${SOURCE_DIR}/Win32Window.cpp)

target_include_directories(${TARGET_NAME} 
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
		${CMAKE_CURRENT_SOURCE_DIR}/../
        )

target_sources(${TARGET_NAME} 
    PRIVATE 
    ${SRC_FILES}
    PUBLIC
    ${INCLUDE_FILES}
    )


