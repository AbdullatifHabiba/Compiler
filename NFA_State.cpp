#include "NFA_State.h"

void NFA_State::addEpsilonTransition(NFA_State *next_state) {
    epsilonTransitions.push_back(next_state);
}

void NFA_State::addTransition(char rule, NFA_State *next_state) {
    transitions[rule].push_back(next_state);
}

bool NFA_State::isFinalState() {
    return this->isFinal;
}

map<char, vector<NFA_State *>> NFA_State::getTransitions() {
    return transitions;
}


NFA_State::NFA_State(bool isFinal) {
    this->isFinal = isFinal;
    this->id=increase_id++;
}

void NFA_State::setFinalState(bool isFinal) {
    this->isFinal = isFinal;
}

NFA_State::~NFA_State() = default;
int NFA_State::increase_id = 1;

void NFA_State::set_id(int a) {
    this->id=a;

}

int NFA_State::get_id() const {
    return this->id;
}
void NFA_State::set_priority(int p){
    this->priority = p;
}
int NFA_State::get_priority() {
    return this->priority;
}
void NFA_State::set_token(string t){
    this->token = t;
}
string NFA_State::get_token() {
    return this->token;
}
