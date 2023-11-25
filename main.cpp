#include <iostream>
#include "Scanner.h"
#include "NFA.h"

int main() {
    // intilize  scanner
    Scanner scanner;

    string file_name ="/home/abdu/CLionProjects/compilers/input.txt";
    scanner.scan(file_name);
    std::vector<char *> words = Scanner::readInput();
//    // size of vector
//    std::cout << words.size() << std::endl;
//
//    for (auto &word : words) {
//        std::cout << word << std::endl;
//    }
// build the NFA
    NFA nfa;
    nfa.buildNFA(words);
    nfa.printNFA();





    return 0;
}

/**
 * scanner
 *
 *
 *
 *
 *
 * /