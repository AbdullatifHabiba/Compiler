// CFGRule.cpp
#include "CFGRule.h"

CFGRule::CFGRule() = default;



CFGRule::~CFGRule() = default;


void CFGRule::setNonTerminal(const std::string& nterminal) {
    this->nonTerminal = nterminal;
}

void CFGRule::addDerivedString(const Token& derivedString) {
    derivedStrings.push_back(derivedString);
}

const std::string& CFGRule::getNonTerminal() const {
    return nonTerminal;
}

const std::vector<Token>& CFGRule::getDerivedStrings() const {
    return derivedStrings;
}


