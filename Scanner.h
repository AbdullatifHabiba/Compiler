//
// Created by abdu on 11/25/23.
//

#ifndef COMPILERS_SCANNER_H
#define COMPILERS_SCANNER_H
#include <fstream>
#include <iostream>
#include <vector>
#include "NFA.h"

using namespace std;
class Scanner {
public:
    Scanner();
    ~Scanner();
    NFA* scan(string pFile );
    static std::vector<char *> readInput();
    map < string , string > identifiers;
private:
    NFA * getWords();
    static void splitInput(const std::string& line);
    string file;

    void parseKeyword(string &input);
    vector<string> tokenTypes;
    NFA* keywords ;
    NFA* punctuation ;
    NFA* finalNFA ;


    void parsePunctuation(string &input);

    void parseExpression(string &input, int &i);

    vector<string> getTokens(string &input);

    vector<string> generatePostfix(vector<string> &tokens);

    void parseDefinition(string &input, int &i);
};


#endif //COMPILERS_SCANNER_H
