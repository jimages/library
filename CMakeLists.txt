cmake_minimum_required(VERSION 3.5)
project(power LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON )
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/build)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})

option(test "Build all tests." OFF)

add_executable(pow
	src/main.cc
	src/pow.cc
	src/pow.h
)

# Set Warning
if ( CMAKE_CXX_COMPILER_ID MATCHES "Clang|AppleClang|GNU" )
	target_compile_options( pow PRIVATE -Wall -Wextra -Wunreachable-code -Wpedantic)
endif()
if ( CMAKE_CXX_COMPILER_ID MATCHES "Clang" )
    target_compile_options( pow PRIVATE -Wweak-vtables -Wexit-time-destructors -Wglobal-constructors -Wmissing-noreturn )
endif()
if ( CMAKE_CXX_COMPILER_ID MATCHES "MSVC" )
    target_compile_options( pow PRIVATE /W4 /w44265 /w44061 /w44062 )
endif()

if (test)
endif ()
