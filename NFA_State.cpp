

#include "NFA_State.h"

void NFA_State::addEpsilonTransition( NFA_State *next_state) {
}

void NFA_State::addTransition( char rule, NFA_State *next_state) {

}

bool NFA_State::isFinalState() {
    return false;
}

map<char, vector<NFA_State *>> NFA_State::getTransitions() {
    return {};
}
map<char, vector<NFA_State *>> NFA_State::getEpsilonTransitions() {
    return {};
}
vector<NFA_State*> NFA_State::getEpsilonClosure() {
    return {};
}



NFA_State::~NFA_State() = default;

NFA_State::NFA_State() = default;
