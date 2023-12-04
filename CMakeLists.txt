cmake_minimum_required(VERSION 3.26)
project(compilers)

set(CMAKE_CXX_STANDARD 17)

add_executable(compilers main.cpp
        NFA.cpp
        NFA.h
        DFA.cpp
        DFA.h
        NFA_State.cpp
        NFA_State.h
        Scanner.cpp
        Scanner.h
        Matcher.cpp
        Matcher.h
        DFA_State.cpp
        DFA_State.h
        Minimize.cpp
        Minimize.h)
