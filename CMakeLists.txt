cmake_minimum_required(VERSION 3.17)
project(virtual_machine)

set(CMAKE_CXX_STANDARD 17)

add_executable(
        virtual_machine main.cpp
        Memory.h Memory.cpp
        Processor.h Processor.cpp
        Types.h Commands/Command.h
        PSW.h)
