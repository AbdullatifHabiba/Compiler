//
// Created by abdu on 11/25/23.
//

#include "DFA_State.h"

void DFA_State::addNFAState(NFA_State *nfaState) {

}

DFA_State::DFA_State(bool isFinal) {

}

map<char, vector<NFA_State *>> DFA_State::getTransitions() {
    return map<char, vector<NFA_State *>>();
}

bool DFA_State::isFinalState() {
    return false;
}

void DFA_State::setFinalState(bool isFinal) {

}

DFA_State::~DFA_State() = default;
