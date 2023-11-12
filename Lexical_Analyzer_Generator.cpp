//
// Created by abdu on 11/12/23.
//

#include <string>
#include "Lexical_Analyzer_Generator.h"

class LexicalAnalyzerGenerator {
public:
    LexicalAnalyzerGenerator(std::string regex);
    void RulesReader(FILE file);
    void constructNFA();
    void convertNFAToDFA();
    void minimizeDFA();
    void emitTransitionTable();
private:
    std::string regex;
    // Add data structures for NFA, DFA, transition table etc.

};

void LexicalAnalyzerGenerator::constructNFA() {
    // Implement this method


}

void LexicalAnalyzerGenerator::convertNFAToDFA() {

}

void LexicalAnalyzerGenerator::minimizeDFA() {

}

void LexicalAnalyzerGenerator::emitTransitionTable() {

}

void LexicalAnalyzerGenerator::RulesReader(FILE file) {

}

class LexicalAnalyzer {
public:
    LexicalAnalyzer(LexicalAnalyzerGenerator generator);
    void analyze(std::string input);
    void insertIntoSymbolTable(std::string identifier);
    void handleError();
private:
    LexicalAnalyzerGenerator generator;
    // Add data structures for symbol table, token class, attribute value etc.
};

void LexicalAnalyzer::analyze(std::string input) {

}

void LexicalAnalyzer::insertIntoSymbolTable(std::string identifier) {

}

void LexicalAnalyzer::handleError() {

}

class Parser {
public:
    Parser(LexicalAnalyzer analyzer);
    void parse();
private:
    LexicalAnalyzer analyzer;
    // Add data structures for syntax tree etc.
};

void Parser::parse() {

}
