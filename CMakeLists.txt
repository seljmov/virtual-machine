cmake_minimum_required(VERSION 3.17)
project(virtual_machine)

set(CMAKE_CXX_STANDARD 17)

add_executable(
        virtual_machine main.cpp
        Memory.cpp Memory.h
        Processor.cpp Processor.h
        Loader.cpp Loader.h
        Types.h PSW.h Exceptions.h Commands/Command.h
        Commands/Conversions.cpp Commands/Conversions.h
        Commands/IntegerArithmetic.cpp Commands/IntegerArithmetic.h
        Commands/RealArithmetic.cpp Commands/RealArithmetic.h
        Commands/Movements.cpp Commands/Movements.h
        Commands/IO.cpp Commands/IO.h
        Commands/IMath.cpp Commands/IMath.h Commands/RMath.cpp Commands/RMath.h Commands/Jumps.cpp Commands/Jumps.h)
