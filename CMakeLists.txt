cmake_minimum_required(VERSION 3.17)
project(bytecodeinterpreter)

set(CMAKE_CXX_STANDARD 20)

add_executable(bytecodeinterpreter
        main.cpp
        Instruction.cpp
        Instruction.hpp BytecodeInterpreter.cpp BytecodeInterpreter.hpp)