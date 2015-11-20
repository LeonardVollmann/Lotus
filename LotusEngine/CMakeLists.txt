cmake_minimum_required(VERSION 2.6)

project(LotusEngine)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${LotusEngine_SOURCE_DIR}/../bin/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${LotusEngine_SOURCE_DIR}/../bin/lib)
set(LotusEngine_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../bin/include)

add_definitions(
	-c
	-Wall
)

if (CMAKE_BUILD_TYPE STREQUAL "Release")
	add_definitions(-O3)
elseif (CMAKE_BUILD_TYPE STREQUAL "Debug")
	add_definitions(-g)
endif (CMAKE_BUILD_TYPE STREQUAL "Release")

file(GLOB_RECURSE HDRS
	${LotusEngine_SOURCE_DIR}/src/*.hpp
	${LotusEngine_SOURCE_DIR}/src/*.h
	${LotusEngine_SOURCE_DIR}/ext/include/stb/*.h
)

file(GLOB_RECURSE SRCS
	${LotusEngine_SOURCE_DIR}/src/*.cpp
	${LotusEngine_SOURCE_DIR}/src/*.c
	${LotusEngine_SOURCE_DIR}/ext/include/stb/*.c
)

add_library(LotusEngine STATIC ${HDRS} ${SRCS})

find_package(OpenGL REQUIRED)

include_directories(
	${LotusEngine_SOURCE_DIR}/headers
	${LotusEngine_SOURCE_DIR}/sources
	${LotusEngine_SOURCE_DIR}/ext/include
)

target_link_libraries( LotusEngine
	${OPENGL_LIBRARIES}
	${LotusEngine_SOURCE_DIR}/ext/lib/libGLEW.1.12.0.dylib
	${LotusEngine_SOURCE_DIR}/ext/lib/libglfw3.3.1.dylib
)
