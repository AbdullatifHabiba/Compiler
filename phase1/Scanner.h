
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
    map < string , string > definitions;
    NFA* getFinalNFA();

private:
    NFA * getWords();
    string file;

    void handleKeywords(string &input);
    NFA* keywords ;
    NFA* punctuation ;
    NFA* finalNFA ;


    void handlePunctuation(string &input);

    void handleExpression(string &input, int &i);

    vector<string> getTokens(string &input);

    static vector<string> createPostfix(vector<string> &tokens);

    void handleDefinition(string &input, int &i);

    static vector<string> handleStack(vector<string> &tokens, stack<string> &s, string &operations, int i);
};


#endif //COMPILERS_SCANNER_H
