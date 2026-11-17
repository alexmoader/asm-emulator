cmake_minimum_required(VERSION 3.10)
project(ProcessorTools VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(${PROJECT_SOURCE_DIR}/include)

add_library(utils STATIC src/utils.cpp)

add_executable(asm src/main_asm.cpp src/assembler.cpp)
target_link_libraries(asm utils)

add_executable(emu src/main_emu.cpp src/emulator.cpp)
target_link_libraries(emu utils)
