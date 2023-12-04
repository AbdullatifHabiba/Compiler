#include "DFA_State.h"
#include<bits/stdc++.h>

int DFA_State::increase_id = 0;
int DFA_State::min_increase_id = 0;

DFA_State::DFA_State()
{
    this -> id = -1;
}

DFA_State:: DFA_State(bool isFinal)
{
    this -> id = min_increase_id++;

}

DFA_State::~DFA_State() {}

int DFA_State::get_id()
{
    return this -> id;
}
string DFA_State::get_token()
{
    return this -> token;
}
bool DFA_State::isFinalState()
{
    return this -> isFinal;
}

DFA_State* DFA_State::get_next(char input)
{
    if (this -> transactions.find(input) == this -> transactions.end())
    {
        DFA_State* d = new DFA_State();
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

void DFA_State::set_content(set<NFA_State *> content) {
    this->content = content;
    bool flag = false;
    for (set<NFA_State*>::iterator i = this->content.begin(); i != this->content.end(); i++)
    {
        NFA_State *temp = *i;
        if(temp->isFinalState())
        {
            set_priority(flag, temp);
            flag = true;
        }
    }
    if (content.size() == 0)
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

map<char, DFA_State *> DFA_State::getTransitions() {
    return this->transactions;
}

void DFA_State::set_token(string s) {
    this->token = s;
}

void DFA_State::set_final(bool f) {
    this->isFinal = f;
}
