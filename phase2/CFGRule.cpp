// CFGRule.cpp
#include "CFGRule.h"

CFGRule::CFGRule() = default;



CFGRule::~CFGRule() = default;


void CFGRule::setNonTerminal(const std::string& non_terminal) {
    this->nonTerminal = non_terminal;
}

void CFGRule::addDerivedString(const vector<Token>& derivedString) {
    derivedStrings.push_back(derivedString);
}

const std::string& CFGRule::getNonTerminal() const {
    return nonTerminal;
}

const std::vector<vector<Token>>& CFGRule::getDerivedStrings() const {
    return derivedStrings;
}

void CFGRule::setDerivedStrings(vector<vector<Token>> &tokens) {
        derivedStrings = tokens;
}


