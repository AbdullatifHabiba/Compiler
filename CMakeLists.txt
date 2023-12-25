cmake_minimum_required(VERSION 3.26)
project(compilers)

set(CMAKE_CXX_STANDARD 17)

add_executable(compilers main.cpp
        phase1/NFA.cpp
        phase1/NFA.h
        phase1/DFA.cpp
        phase1/DFA.h
        phase1/NFA_State.cpp
        phase1/NFA_State.h
        phase1/Scanner.cpp
        phase1/Scanner.h
        phase1/Matcher.cpp
        phase1/Matcher.h
        phase1/DFA_State.cpp
        phase1/DFA_State.h
        phase1/Minimize.cpp
        phase1/Minimize.h
        phase2/CFGRule.cpp
        phase2/CFGRule.h
        phase2/CFGReader.cpp
        phase2/CFGReader.h
        phase2/Token.cpp
        phase2/Token.h
        phase2/Combiner.cpp
        phase2/Combiner.h
        phase2/ParsingTable.cpp
        phase2/ParsingTable.h
        phase2/LL1_Generator.cpp)
