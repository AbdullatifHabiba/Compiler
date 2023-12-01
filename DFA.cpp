//
// Created by abdu on 11/25/23.
//

#include "DFA.h"
#include <queue>
#include <iostream>

DFA::DFA() {

}

DFA::~DFA() {

}
set<NFA_State*> Mapped;
//    std::cout << "State: " << s->get_id() <<" : "<<endl;
// get each nfa state epsilon closure
void DFA::e_closure(NFA_State *s)
{
    set<NFA_State*> v ;
    for (NFA_State *x : s->getTransitions()['@']) {
        v.insert(x);
    }
    Mapped.insert(s);
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
        Mapped.clear();
        NFA_State *state = *i;
        e_closure(state);
        set<NFA_State*> s = Mapped;
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
        set<NFA_State*> s1 ;
        for (NFA_State *x : state->getTransitions()[input]) {
            s1.insert(x);
        }
        set<NFA_State*> s2 = e_closure(s1);
        returned_set.insert(s2.begin(), s2.end());
    }
    return returned_set;
}

set<DFA_State*> DFA::convert_NFA_to_DFA(NFA_State* start)
{
    queue <DFA_State*> unmarked;      /*queue to add unmarked new D_states*/
    set<DFA_State*> DFA;              /*returned DFA graphe*/
    Mapped.clear();
    e_closure(start);

    DFA_State *s = new DFA_State();
    s->set_content(Mapped);
    DFA.insert(s);
    unmarked.push(s);
    set<char> alpha = get_alpha(start);
    while(!unmarked.empty())
    {
        DFA_State *temp = unmarked.front();
        unmarked.pop();

        /*loop for all inputs on set alpha*/
        for (std::set<char>::iterator it=alpha.begin(); it!=alpha.end(); ++it)
        {
            /*get destination from source temp on input it */
            set<NFA_State*> destination = move(temp->get_content(),*it);


            /*chech if the dest is not in DFA*/
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
                // cout << "rererere :::: " << dest -> get_name() << endl;
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

set<char> DFA::get_alpha(NFA_State* S)
{
    set <char> alpha;

    queue < NFA_State* > current;
    set < NFA_State* > visited;

    current.push (S);
    visited.insert (S);

    while ( !current.empty() )
    {
        NFA_State* x = current.front();
        current.pop();
        for(auto it = x->getTransitions().begin(); it != x->getTransitions().end(); ++it)
        {
            alpha.insert (it->first);
            for (NFA_State* n : (it -> second) )
            {
                if (visited.find(n) == visited.end())
                {
                    visited.insert (n);
                    current.push (n);
                }
            }
        }
    }
    alpha.erase('@');
    alpha.erase('\0');
    for (std::set<char>::iterator it=alpha.begin(); it!=alpha.end(); ++it){
        cout << *it << "  ";
    }
    return alpha;
}


