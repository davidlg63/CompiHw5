cmake_minimum_required(VERSION 3.15)
project(hw5_1)

set(CMAKE_CXX_STANDARD 17)

add_executable(hw5_1 bp.cpp CodeGenerator.cpp SymbolTableManager.cpp SymbolTableEntry.cpp SymbolTable.cpp Symbols.cpp RegisterGenerator.cpp hw3_output.cpp)