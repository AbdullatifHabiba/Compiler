//
// Created by abdu on 11/25/23.
//

#ifndef COMPILERS_SCANNER_H
#define COMPILERS_SCANNER_H
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;
class Scanner {
public:
    Scanner();
    ~Scanner();
    void scan(string pFile );
    static std::vector<char *> readInput();
private:
    void getWords();
    static void splitInput(const std::string& line);
    string file;
};


#endif //COMPILERS_SCANNER_H
