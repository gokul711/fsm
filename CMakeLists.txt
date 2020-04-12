cmake_minimum_required(VERSION 3.0)
cmake_policy(SET CMP0048 NEW)

project(FSM VERSION 0.0.1 )
project(FSM CXX C)
set(CMAKE_CXX_STANDARD 11)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

#Enable debug build
add_compile_options ("-g")
add_subdirectory( src )     # FSM implementation source
add_subdirectory( test ) # test application

# ============================================================================
# Project includes
# ============================================================================

target_include_directories(FSM PRIVATE ${PROJECT_SOURCE_DIR}/inc)



