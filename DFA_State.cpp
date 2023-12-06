#include "DFA_State.h"
#include<bits/stdc++.h>

#include <utility>

int DFA_State::increase_id = 0;
int DFA_State::min_increase_id = 0;

DFA_State::DFA_State(int id)
{
    this -> id = id;
}


DFA_State:: DFA_State(bool isFinal)
{
    this -> id = min_increase_id++;
}

DFA_State::~DFA_State() = default;

int DFA_State::get_id() const
{
    return this -> id;
}
string DFA_State::get_token()
{
    return this -> token;
}
bool DFA_State::isFinalState() const
{
    return this -> isFinal;
}

DFA_State* DFA_State::get_next(char input)
{
    if (this -> transactions.find(input) == this -> transactions.end())
    {
        auto* d = new DFA_State();
        return d;
    }
    else return this -> transactions.find(input)->second;
}
set<NFA_State*> DFA_State::get_content()
{
    return this -> content;
}

void DFA_State::addTransition(char ch, DFA_State *state)
{
    this -> transactions.insert(std::pair<char, DFA_State*>(ch, state));
}

void DFA_State::set_content(const set<NFA_State *>& content1) {
    this->content = content1;
    bool flag = false;
    for (auto temp : this->content)
    {
        if(temp->isFinalState())
        {
            set_priority(flag, temp);
            flag = true;
        }
    }
    if (content.empty())
    {
        this->token =  "Dead State";
    }
    this->isFinal = flag;
    this->id = increase_id++;
}

void DFA_State::set_priority(bool flag, NFA_State *temp) {
    if (!flag)
    {
        this -> token = temp-> get_token();
        this -> priority = temp-> get_priority();
    }
    else
    {
        if (this -> priority > temp -> get_priority())
        {
            this -> token = temp->get_token();
            this -> priority = temp->get_priority();
        }
    }
}

map<char, DFA_State *> DFA_State::getTransitions() const {
    return this->transactions;
}

void DFA_State::set_token(string s) {
    this->token = std::move(s);
}

void DFA_State::set_final(bool f) {
    this->isFinal = f;
}

int DFA_State::get_priority() const {
    return this->priority;
}

void DFA_State::set_priority(int priority) {
    this->priority = priority;

}

DFA_State::DFA_State() = default;

