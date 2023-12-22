//
// Created by abdu on 12/19/23.
//

#include "Token.h"

Token::Token() = default;


void Token::setName(const std::string& name1) {
    this->name = name1;
}




const std::string &Token::getName() const {
    return name;
}



void Token::setIsTerminal(bool isTerminal1) {
    Token::isTerminal = isTerminal1;
}

Token::~Token() = default;



