//
// Created by abdu on 11/25/23.
//

#include "DFA.h"
#include <bits/stdc++.h>
#include "NFA_State.h"
#include "DFA_State.h"

DFA::DFA() {}

DFA::~DFA() {}

void DFA::e_closure(NFA_State *s)
{
    std::vector<NFA_State*> transitionsVector = s->getTransitions()['@'];
    // Convert the vector to a set
    std::set<NFA_State*> v(transitionsVector.begin(), transitionsVector.end());

    returned.insert(s);
    if(v.size() == 0)
    {
        return;
    }
    for (set<NFA_State*>::iterator i = v.begin(); i != v.end(); i++)
    {
        NFA_State *state  = *i;
        e_closure(state);
    }
}

set<NFA_State*> DFA::e_closure(set<NFA_State*> T)
{
    set<NFA_State*> returned_set;
    for (set<NFA_State*>::iterator i = T.begin(); i != T.end(); i++)
    {
        returned.clear();
        NFA_State *state = *i;
        e_closure(state);
        set<NFA_State*> s = returned;
        returned_set.insert(s.begin(), s.end());
    }
    return returned_set;
}

set<NFA_State*> DFA::move(set<NFA_State*> T, char input)
{
    set<NFA_State*> returned_set;
    for (set<NFA_State*>::iterator i = T.begin(); i != T.end(); i++)
    {
        NFA_State *state = *i;
        std::vector<NFA_State*> transitionsVector = state->getTransitions()[input];
        // Convert the vector to a set
        std::set<NFA_State*> s1(transitionsVector.begin(), transitionsVector.end());

        set<NFA_State*> s2 = e_closure(s1);
        returned_set.insert(s2.begin(), s2.end());
    }
    return returned_set;
}

set<DFA_State*> DFA::Converter(NFA_State* start)
{
    queue <DFA_State*> unmarked;
    set<DFA_State*> DFA;
    e_closure(start);
    DFA_State *s = new DFA_State();
    s->set_content(returned);
    DFA.insert(s);
    unmarked.push(s);
    set<char> alpha = get_alpha(start);
    while(!unmarked.empty())
    {
        DFA_State *temp = unmarked.front();
        unmarked.pop();
        for (std::set<char>::iterator it=alpha.begin(); it!=alpha.end(); ++it)
        {
            set<NFA_State*> destination = move(temp->get_content(),*it);
            bool flag = false;
            DFA_State* test ;
            for (std::set<DFA_State*>::iterator itr =DFA.begin(); itr !=DFA.end(); ++itr)
            {
                DFA_State* d = *itr;
                if(d->get_content() == destination)
                {
                    flag = true;
                    test = d;
                    break;

                }
            }

            if (!flag )
            {
                DFA_State *dest = new DFA_State();
                dest->set_content(destination);
                DFA.insert(dest);
                unmarked.push(dest);
                temp->addTransition(*it,dest);
            }
            else
            {
                temp->addTransition(*it,test);
            }
        }
    }
    return DFA;
}

set<char> DFA::get_alpha(NFA_State* s)
{
    set <char> alpha;
    queue < NFA_State* > current;
    set < NFA_State* > visited;
    current.push (s);
    visited.insert (s);

    while ( !current.empty() )
    {
        NFA_State* x = current.front();
        current.pop();
        auto transitions = x->getTransitions();
        for (auto it = transitions.begin(); it != transitions.end(); ++it)
        {
            alpha.insert(it->first);
            for (NFA_State * n : it->second)
            {
                if (n != nullptr && visited.find(n) == visited.end())
                {
                    visited.insert(n);
                    current.push(n);
                }
            }
        }
    }
    alpha.erase('@');
    alpha.erase('\0');

    return alpha;
}

void DFA::printDFA(set<DFA_State*> Dfa)
{
    for (auto Trans : Dfa) {
        typedef map<char, DFA_State* > :: const_iterator MapIterator;
        cout<< "state " << Trans->get_id() << " Final ? "<<Trans->isFinalState()<<"  ";
        cout<< "Token: "<< Trans->get_token();
        cout<<endl;
        for (MapIterator iter = Trans->transactions.begin(); iter != Trans->transactions.end(); iter++)
        {
            cout  << "    --->> " << iter->first << "  >>--- "<< iter->second->get_id() <<endl;
        }
    }

}

void DFA::printDFA_data(set<DFA_State*> Dfa)
{
    for (auto Trans : Dfa) {
        typedef map<char, DFA_State *>::const_iterator MapIterator;
        cout << "state " << Trans->get_id();//<< " Final ? "<<this->isFinalState()<<"  ";
        cout << "  --> Token: " << Trans->get_token();
        cout << endl;
        for (auto *it: Trans->get_content()) {
            cout << " , State " << it->get_id();
        }
        cout << endl;
    }
}
