cmake_minimum_required(VERSION 2.6)

set(TARGET_NAME platform)
add_library(${TARGET_NAME} SHARED)

# begin use cmake 3.0 feature
# set path
set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Include)
set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Src)

set(INCLUDE_FILES ${INCLUDE_DIR}/Win32Window.h
)

set(SRC_FILES ${SOURCE_DIR}/Win32Window.cpp)

target_include_directories(${TARGET_NAME} 
    PUBLIC
        ${INCLUDE_DIR}
        )

target_sources(${TARGET_NAME} 
    PRIVATE 
    ${SRC_FILES}
    PUBLIC
    ${INCLUDE_FILES}
    )

message(STATUE ${CMAKE_BINARY_DIR} ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})





