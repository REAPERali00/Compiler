cmake_minimum_required(VERSION 3.8)

project(compiler)

# Specify the directory containing the source files
set(CODE_DIR "${CMAKE_SOURCE_DIR}/code")

# Collect all source files in the specified directory
file(GLOB SOURCES "${CODE_DIR}/*.c" "${CODE_DIR}/*.h")

# Add source to this project's executable: check name and dependencies
add_executable(compiler ${SOURCES})

# TO_DO: Add tests and install targets if needed.
