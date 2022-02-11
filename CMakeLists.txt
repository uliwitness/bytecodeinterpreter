cmake_minimum_required(VERSION 3.17)
project(bytecodeinterpreter)

set(CMAKE_CXX_STANDARD 20)

add_library(bytecodeinterpreter_internals
        Instruction.cpp
        Instruction.hpp
        BytecodeInterpreter.cpp
        BytecodeInterpreter.hpp)

add_executable(bytecodeinterpreter
        main.cpp)

target_link_libraries(bytecodeinterpreter bytecodeinterpreter_internals)