cmake_minimum_required(VERSION 3.10)

project(SneakersProject)

set(APP_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(SOURCES
    ${SOURCE_DIR}/sneakers.c
)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

option(BUILD_SHARED_LIBS "Build shared library" OFF)

if(BUILD_SHARED_LIBS)
    add_library(UTIL_LIB SHARED ${SOURCES})
else()
    add_library(UTIL_LIB STATIC ${SOURCES})
endif()

add_executable(main ${APP_DIR}/main.c)
target_link_libraries(main UTIL_LIB)
