cmake_minimum_required(VERSION 2.6)

project(Lotus)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_definitions(
	-g
	-c
	-Wall
)

if ( CMAKE_BUILD_TYPE STREQUAL "" )
	set(
		CMAKE_BUILD_TYPE
			"Debug"
		CACHE STRING
			"Choose the type of build, options are: None (CMAKE_CXX_FLAGS or CMAKE_C_FLAGS used) \"Debug\" \"Release\" \"RelWithDebInfo\" \"MinSizeRel\"."
		FORCE
	)
endif ( CMAKE_BUILD_TYPE STREQUAL "" )

if ( CMAKE_BUILD_TYPE STREQUAL "Release" )
add_definitions( -O3 )
endif ( CMAKE_BUILD_TYPE STREQUAL "Release" )

file(GLOB_RECURSE HDRS 
	${Lotus_SOURCE_DIR}/src/*.hpp
	${Lotus_SOURCE_DIR}/src/*.h
)

file(GLOB_RECURSE SRCS
	${Lotus_SOURCE_DIR}/src/*.cpp
	${Lotus_SOURCE_DIR}/src/*.c
)

add_executable(Lotus ${HDRS} ${SRCS})

SET(Lotus_CMAKE_DIR "${Lotus_SOURCE_DIR}/cmake")

find_package(OpenGL REQUIRED)
INCLUDE(${Lotus_CMAKE_DIR}/FindGLEW.cmake)
INCLUDE(${Lotus_CMAKE_DIR}/FindGLFW3.cmake)

include_directories(
	${Lotus_SOURCE_DIR}/headers
	${Lotus_SOURCE_DIR}/sources
	${OPENGL_INCLUDE_DIRS}
	${GLEW_INCLUDE_DIRS}
	${GLFW3_INCLUDE_DIRS}
)

target_link_libraries( Lotus
	${OPENGL_LIBRARIES}
	${GLEW_LIBRARIES}
	${GLFW3_LIBRARIES}
)