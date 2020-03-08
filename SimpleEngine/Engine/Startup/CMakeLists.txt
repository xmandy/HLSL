cmake_minimum_required(VERSION 2.6)

project(Startup)

#file(GLOB_RECURSE PLATFORM_HEADERS ${CMAKE_SOURCE_DIR}/Platform/Include/*.h)

#source_group("Platform Include" FILES ${PLATFORM_HEADERS})

# set path
set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Public)
set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Private)
list(APPEND INCLUDE_DIR ${AllEngineIncludePath})

#link_libraries(Common Components Platform Game)

LIST(APPEND INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/..)
include_directories(${INCLUDE_DIR})
link_directories(${AllEngineLinkPath})

add_executable(${PROJECT_NAME} WIN32 ${SOURCE_DIR}/win_main.cpp ${PLATFORM_HEADERS})


#get_directory_property(OUT_VAR LINK_DIRECTORIES)
#message(STATUS "link_directories: " ${OUT_VAR})

target_link_libraries(${PROJECT_NAME} DirectXTK)


add_dependencies(${PROJECT_NAME} Common)
target_link_libraries(${PROJECT_NAME} Common)

add_dependencies(${PROJECT_NAME} Platform)
target_link_libraries(${PROJECT_NAME} Platform)

add_dependencies(${PROJECT_NAME} Game)
target_link_libraries(${PROJECT_NAME} Game)


#source_group("Header Files" REGULAR_EXPRESSION "^$")
#source_group("Some Other Source Group" REGULAR_EXPRESSION "\\.h$")
#source_group(""  REGULAR_EXPRESSION "\\.h$")


