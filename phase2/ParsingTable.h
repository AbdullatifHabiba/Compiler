//
// Created by u s e r on 21/12/2023.
//

#ifndef COMPILERS_PARSINGTABLE_H
#define COMPILERS_PARSINGTABLE_H
#include "Token.h"
#include <unordered_map>
#include "CFGRule.h"
#include <bits/stdc++.h>
#include "CFGReader.h"


class ParsingTable{

public:
//    using THALB =std::unordered_map<Token, std::unordered_map<Token, std::pair<std::string, std::vector<Token>>>>;
    ParsingTable(const  std::map<std::string, CFGRule*> &rules,const string startState);


    /**
     * Returns a first set of any symbol
     * @param symbol
     * @return first_set
     */
    std::set<Token> get_first(Token& symbol);//
    /**
     * Returns the production that derives a symbol first in the first symbol
     * @param non_terminal non_terminal of interest
     * @param first first symbol that is in the first_set of the above non_terminal
     * @return production
     */
    std::vector<Token> Production_of_first(Token& non_terminal, Token& first);

    std::set<Token> get_follow(Token& symbol);//

    void Create_table();

    std::pair<std::string, std::vector<Token>> get_entry(Token& non_terminal, Token& terminal);

    void Print_table(std::string path);

    std::string get_production_name(std::vector<Token> vec);
    Token eps_symbol = Token("\'\\L\'");

private:
    std::map<Token , CFGRule > grammar;
    std::map<std::string, std::set<Token>> first ;
    std::map<std::string, std::set<Token>> follow ;
    std::vector<Token> nonTerminalsList;
    std::set<Token> TerminalsList;

    map <Token,map <Token,pair<string,vector<Token>>>> Table;
    void First_computation(const Token& non_terminal,const CFGRule& prods);
    void Terminals_follow_nonTerminals();
    void Right_most_follow();
};

#endif //COMPILERS_PARSINGTABLE_H
