cmake_minimum_required(VERSION 2.6)

project(Game)
set(TARGET_NAME ${PROJECT_NAME})
add_library(${TARGET_NAME})

# begin use cmake 3.0 feature
# set path

set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/GameCore/Public)
set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/GameCore/Private)

file(GLOB_RECURSE INCLUDE_FILES ${INCLUDE_DIR}/*.h)
file(GLOB_RECURSE SRC_FILES ${SOURCE_DIR}/*.cpp)

set(INCLUDE_FILES "")
set(SRC_FILES "")

file(GLOB children ${CMAKE_CURRENT_SOURCE_DIR}/*)

foreach(child ${children})
    if(IS_DIRECTORY ${child})
        cmpDirectoryFiles(${child} INCLUDE_FILES SRC_FILES)
    endif()
endforeach()

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${INCLUDE_FILES})
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SRC_FILES})

# for finegrained controll, add file one by one
#set(INCLUDE_FILES ${INCLUDE_DIR}/Win32Window.h
#)
#set(SRC_FILES ${SOURCE_DIR}/Win32Window.cpp)

#set(DEPEND_LIBS "Common" "Components")

MACRO (cmp_IDE_SOURCE_PROPERTIES SOURCE_PATH HEADERS SOURCES)
    STRING(REPLACE "/" "\\\\" source_group_path ${SOURCE_PATH}  )
    source_group(${source_group_path} FILES ${HEADERS} ${SOURCES})
ENDMACRO (cmp_IDE_SOURCE_PROPERTIES NAME HEADERS SOURCES INSTALL_FILES)

#cmp_IDE_SOURCE_PROPERTIES( "Source/Lib" ${INCLUDE_FILES} ${SRC_FILEs})
#source_group(""  FILES ${INCLUDE_FILES} ${SRC_FILES})
#source_group("SourceTest"  FILES ${INCLUDE_FILES} ${SRC_FILES})

#source_group("Header Files2" FILES ${INCLUDE_FILES})

#add_dependencies(${TARGET_NAME} ${DEPEND_LIBS})
#target_link_libraries(${TARGET_NAME} ${DEPEND_LIBS})

add_dependencies(${TARGET_NAME} Common)
#target_link_libraries(${TARGET_NAME} Common)
#add_dependencies(${TARGET_NAME} Components)
#target_link_libraries(${TARGET_NAME} Components)

target_include_directories(${TARGET_NAME} 
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
		${CMAKE_CURRENT_SOURCE_DIR}/../
		${CMAKE_CURRENT_SOURCE_DIR}/Public
        ${AllEngineIncludePath}
        )

target_sources(${TARGET_NAME} 
    PRIVATE 
    ${SRC_FILES}
    PUBLIC
    ${INCLUDE_FILES}
    )


