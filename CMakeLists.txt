cmake_minimum_required(VERSION 3.8)
project(compiler C)

# Set C standard
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Set output directories to follow the discussed structure
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# Define project structure paths
set(SRC_DIR "${CMAKE_SOURCE_DIR}/src")
set(INCLUDE_DIR "${CMAKE_SOURCE_DIR}/include")
set(TEST_DIR "${CMAKE_SOURCE_DIR}/tests")
set(DOC_DIR "${CMAKE_SOURCE_DIR}/doc")
set(INPUT_DIR "${CMAKE_SOURCE_DIR}/input")
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

# Collect all source files
file(GLOB_RECURSE SOURCES "${SRC_DIR}/*.c")

# Include header files
include_directories(${INCLUDE_DIR})

# Define the executable
add_executable(compiler ${SOURCES})

# Enable warnings for better code quality
target_compile_options(compiler PRIVATE -Wall -Wextra -Wpedantic)

# Enable testing if needed
enable_testing()

# Installation rule (optional)
install(TARGETS compiler DESTINATION bin)
