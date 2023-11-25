

#include "NFA_State.h"

void NFA_State::addEpsilonTransition( NFA_State *next_state) {
}

void NFA_State::addTransition( char rule, NFA_State *next_state) {

}

bool NFA_State::isFinalState()  {
    return this->isFinal ;
}

map<char, vector<NFA_State *>> NFA_State::getTransitions() {
    return {};
}
vector<NFA_State*> NFA_State::getEpsilonClosure() {
    return {};
}

NFA_State::NFA_State(bool isFinal) {
    this->isFinal = isFinal;

}

void NFA_State::setFinalState(bool isFinal) {
    this->isFinal = isFinal;

}


NFA_State::~NFA_State() = default;

