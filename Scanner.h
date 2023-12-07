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
    map < string , string > identifiers;
    NFA* getFinalNFA();

private:
    NFA * getWords();
    string file;

    void handleKeywords(string &input);
    vector<string> tokenTypes;
    NFA* keywords ;
    NFA* punctuation ;
    NFA* finalNFA ;


    void handlePunctuation(string &input);

    void handleExpression(string &input, int &i);

    vector<string> getTokens(string &input);

    static vector<string> createPostfix(vector<string> &tokens);

    void handleDefinition(string &input, int &i);

    void processInput(string &input, int &i, string &finalExpression);
};


#endif //COMPILERS_SCANNER_H
