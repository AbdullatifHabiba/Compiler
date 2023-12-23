//
// Created by abdu on 12/23/23.
//

#ifndef COMPILERS_COMBINER_H
#define COMPILERS_COMBINER_H

#include "Token.h"
#include <map>
#include <vector>
#include <stack>
using namespace std;
class Combiner {
public:
    //set the lexical terminals
    void setLexicalTerminals(const vector<string>& lexical_terminals);
    //set the input_table
    void setTable(const map <Token,map <Token,pair<string,vector<Token>>>>& input_table);
    //LL_Parse the lexical terminals with the input_table
    void LL_Parse(const Token& start);

private:
   static void print_stack(stack<Token> s,std::ofstream& output_file);
    map <Token,map <Token,pair<string,vector<Token>>>> table;
    vector<string> lexical_terminals;
    stack<Token> parse_stack;


};


#endif //COMPILERS_COMBINER_H
