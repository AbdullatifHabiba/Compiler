//
// Created by abdu on 12/19/23.
//

#include "Token.h"

Token::Token() = default;


void Token::setName(const std::string& name) {
    this->name = name;
}




const std::string &Token::getName() const {
    return name;
}

bool Token::isTerminal1() const {
    return isTerminal;
}

void Token::setIsTerminal(bool isTerminal1) {
    Token::isTerminal = isTerminal1;
}

Token::~Token() = default;



