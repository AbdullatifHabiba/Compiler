cmake_minimum_required(VERSION 3.26)
project(compilers)

set(CMAKE_CXX_STANDARD 17)

add_executable(compilers main.cpp
        Lexical_Analyzer_Generator.cpp
        Lexical_Analyzer_Generator.h)
