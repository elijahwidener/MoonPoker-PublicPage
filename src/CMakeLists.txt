# src/CMakeLists.txt
#
# CMake file for the binary directory.

cmake_minimum_required(VERSION 3.10)
include(external)

# MoonPoker core functionality library.
file(
  GLOB_RECURSE moon_poker_core_sources
  LIST_DIRECTORIES False
  CONFIGURE_DEPENDS "core/*.cpp")
list(FILTER moon_poker_core_sources INCLUDE REGEX "core/.*.cpp")
add_library(moon_poker_core OBJECT)
target_sources(moon_poker_core PRIVATE ${moon_poker_core_sources})
target_include_directories(
  moon_poker_core
  PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include"
  PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/include/MoonPoker")

# Top-level executable
add_executable(moon_poker)
target_sources(moon_poker PRIVATE nlh_main.cpp)
target_link_libraries(moon_poker PRIVATE moon_poker_core)
