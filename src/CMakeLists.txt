cmake_minimum_required(VERSION 3.16)

set(ROCKET_VERSION "0.1.0")
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
include_directories(${CMAKE_CURRENT_SOURCE_DIR}
                    ${CMAKE_SOURCE_DIR}/../dependencies/include
                    ${OPENGL_INCLUDE_DIR}
                    )
link_directories(${CMAKE_SOURCE_DIR}../dependencies/lib)

set(SOURCES REngine.cpp)

add_library(rocket STATIC ${SOURCES})
add_subdirectory(audio)
add_subdirectory(components)
add_subdirectory(graphics)
add_subdirectory(input)
add_subdirectory(materials)
add_subdirectory(math)
add_subdirectory(networking)
add_subdirectory(platform)
add_subdirectory(types)
add_subdirectory(ui)
add_subdirectory(utilities)

target_link_libraries(rocket ${OPENGL_LIBRARY} librocket-deps.a)

include(GNUInstallDirs)

# install rocket
install( TARGETS rocket
    EXPORT rocket-config
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

install(DIRECTORY
	${CMAKE_SOURCE_DIR}/audio
	${CMAKE_SOURCE_DIR}/components
	${CMAKE_SOURCE_DIR}/graphics
	${CMAKE_SOURCE_DIR}/input
	${CMAKE_SOURCE_DIR}/materials
	${CMAKE_SOURCE_DIR}/math
	${CMAKE_SOURCE_DIR}/networking
	${CMAKE_SOURCE_DIR}/platform
	${CMAKE_SOURCE_DIR}/types
	${CMAKE_SOURCE_DIR}/ui
	${CMAKE_SOURCE_DIR}/utilities
	DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
    FILES_MATCHING PATTERN "*.h"
)
install(FILES
	${CMAKE_SOURCE_DIR}/common.h
	${CMAKE_SOURCE_DIR}/REngine.h
	DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)
