//
// Created by abdu on 11/25/23.
//

#include "DFA_State.h"
#include <iostream>
#include <set>
int DFA_State::increase_id = 1;
DFA_State::DFA_State()
{
    this->id = increase_id++;
}

void DFA_State::set_content(const set<NFA_State *>& content_){
    this->content = content_;
    bool flag = false;
    for (auto temp : content_)
    {
        if(temp->isFinalState())
        {
            if (!flag)
            {
                this -> token = temp-> get_token();
                cout<< "returned priority is "<< temp-> get_priority()<<endl;
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
            flag = true;
        }
    }
    if (content_.empty())
    {
        this->token =  "Dead State";
    }
    this->isFinal = flag;
}

void DFA_State::set_priority(bool flag, NFA_State* temp ) {

}

set<NFA_State*> DFA_State::get_content()
{
    return this -> content;
}

map<char, DFA_State*> DFA_State::getTransitions() const {
    return this->transactions;
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

void DFA_State::addTransition(char ch, DFA_State *state)
{
    this -> transactions.insert(std::pair<char, DFA_State*>(ch, state));
}

int DFA_State::get_id() const
{
    return this -> id;
}

string DFA_State::get_token()
{
    return this -> token;
}

DFA_State::~DFA_State() = default;
