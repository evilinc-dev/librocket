cmake_minimum_required(VERSION 3.16)

set(RTECH_VERSION "0.1.0")
string(TIMESTAMP TODAY "%Y/%m/%d")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

### Require out-of-source builds
file(TO_CMAKE_PATH "${PROJECT_BINARY_DIR}/CMakeLists.txt" LOC_PATH)
if(EXISTS "${LOC_PATH}")
    message(FATAL_ERROR "You cannot build in a source directory (or any directory with a CMakeLists.txt file). Please make a build subdirectory. Feel free to remove CMakeCache.txt and CMakeFiles.")
endif()

### Set C++ Standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project(rocket CXX)

find_package(OpenGL REQUIRED)

message("${CMAKE_SOURCE_DIR}")
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include
                    ${CMAKE_SOURCE_DIR}/../dependencies/include
                    ${OPENGL_INCLUDE_DIR}
                    )
link_directories(${CMAKE_SOURCE_DIR}../dependencies/lib)

file(GLOB_RECURSE SOURCES
    **.cpp
    **.c
    **.h
    **.hpp
    **.inl
)

add_library(rocket STATIC ${SOURCES})

target_link_libraries(rocket ${OPENGL_LIBRARY} librocket-deps.a)

include(GNUInstallDirs)

# install rocket
install( TARGETS rocket
    EXPORT rtech-config
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR} )

install( DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR} )
