cmake_minimum_required(VERSION 2.6)

project(Sandbox)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${Sandbox_SOURCE_DIR}/../bin)

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
	${Sandbox_SOURCE_DIR}/src/*.hpp
	${Sandbox_SOURCE_DIR}/src/*.h
)

file(GLOB_RECURSE SRCS
	${Sandbox_SOURCE_DIR}/src/*.cpp
	${Sandbox_SOURCE_DIR}/src/*.c
)

add_executable(Sandbox ${HDRS} ${SRCS})

set(Sandbox_CMAKE_DIR "${Sandbox_SOURCE_DIR}/../cmake")

find_package(OpenGL REQUIRED)
include(${Sandbox_CMAKE_DIR}/FindGLEW.cmake)
include(${Sandbox_CMAKE_DIR}/FindGLFW3.cmake)

include_directories(
	${Sandbox_SOURCE_DIR}/headers
	${Sandbox_SOURCE_DIR}/sources
	${Sandbox_SOURCE_DIR}/../LotusEngine/src
	${OPENGL_INCLUDE_DIRS}
	${GLEW_INCLUDE_DIRS}
	${GLFW3_INCLUDE_DIRS}
)

target_link_libraries( Sandbox
	LotusEngine
	${OPENGL_LIBRARIES}
	${GLEW_LIBRARIES}
	${GLFW3_LIBRARIES}
)
