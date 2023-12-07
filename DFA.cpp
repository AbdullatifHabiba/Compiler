#include "DFA.h"
#include <bits/stdc++.h>
#include "DFA_State.h"

DFA::DFA() = default;

DFA::~DFA() = default;

set<NFA_State*> returned;

void DFA::e_closure(NFA_State *s)
{
    std::vector<NFA_State*> transitionsVector = s->getTransitions()['@'];
    // Convert the vector to a set
    std::set<NFA_State*> v(transitionsVector.begin(), transitionsVector.end());
    returned.insert(s);
    if(v.empty())
    {
        return;
    }
    for (auto state : v)
    {
        e_closure(state);
    }
}

set<NFA_State*> DFA::e_closure(const set<NFA_State*>& T)
{
    set<NFA_State*> returned_set;
    for (auto NFA_State : T)
    {
        returned.clear();
        e_closure(NFA_State);
        auto f = returned;
        returned_set.insert(f.begin(), f.end());
    }
    return returned_set;
}

set<NFA_State*> DFA::reduce(const set<NFA_State*>& T, char input)
{
    set<NFA_State*> returned_set;
    for (auto state : T)
    {
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
    returned.clear();
    e_closure(start);
    auto *s = new DFA_State();
    s->set_content(returned);
    DFA.insert(s);
    unmarked.push(s);
    set<char> alpha = get_all_inputs(start);
    while(!unmarked.empty())
    {
        DFA_State *temp = unmarked.front();
        unmarked.pop();
        for (char it : alpha)
        {
            set<NFA_State*> destination = reduce(temp->get_content(), it);
            bool flag = false;
            DFA_State* test ;
            for (auto d : DFA)
            {
                if(d->get_content() == destination)
                {
                    flag = true;
                    test = d;
                    break;
                }
            }

            if (!flag )
            {
                auto *dest = new DFA_State();
                dest->set_content(destination);
                DFA.insert(dest);
                unmarked.push(dest);
                temp->addTransition(it,dest);
            }
            else
            {
                temp->addTransition(it,test);
            }
        }
    }
    return DFA;
}

set<char> DFA::get_all_inputs(NFA_State* s)
{
    set <char> alpha;
    queue < NFA_State* > current;
    set < NFA_State* > visited;
    current.push (s);
    visited.insert (s);

    while (!current.empty()) {
        NFA_State *x = current.front();
        current.pop();
        auto transitions = x->getTransitions();
        for (auto & transition : transitions) {
            alpha.insert(transition.first);

            for (NFA_State * n : transition.second)
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

void DFA::printDFA(const set<DFA_State*>& Dfa)
{
    for (auto Trans : Dfa) {
        typedef map<char, DFA_State* > :: const_iterator MapIterator;
        cout<< "state " << Trans->get_id() << " Final ? "<<Trans->isFinalState()<<"  ";
        cout<< "Token: "<< Trans->get_token();
        cout<<endl;
        for (auto & transaction : Trans->transactions)
        {
            cout  << "    --->> " << transaction.first << "  >>--- "<< transaction.second->get_id() <<endl;
        }
    }

}
void DFA::printTransitionTable(const set<DFA_State*>& Dfa)
{
    // print the transition table of the DFA row by row by iterating over the DFA set and print state id and its transitions and extract trs.txt file
    // declare the output file
    ofstream out("trs.txt");

    cout << "DFA Transition Table" << endl;
    cout << "-------------------" << endl;

    cout << endl;
    // print the header of the rows
    cout << "S\t    ";
    out << "S\t    ";
    // get all the alphabet of the DFA
    set<char> alphabet;
    for (auto state : Dfa)
    {
        for (auto trs: state->getTransitions())
        {
            alphabet.insert(trs.first);
        }
    }
    for (auto ch : alphabet)
    {
        cout << ch << "\t";
        out << ch << "\t";
    }
cout << endl;
out << endl;



    for(auto state : Dfa)
    {
        cout << state->get_id()<<"("<< state->get_token()<< ")\t";

        out << state->get_id() <<"("<< state->get_token()<< ")\t";
        for(auto trs: state->getTransitions())
        {
            cout << trs.second->get_id() << "\t";
            out << trs.second->get_id() << "\t";
        }
        cout << endl;
        out << endl;
    }
    out.close();





}

void DFA::printDFA_data(const set<DFA_State*>& Dfa)
{
    for (auto Trans : Dfa) {
        typedef map<char, DFA_State *>::const_iterator MapIterator;
        cout << "state " << Trans->get_id();//<< " Final ? "<<this->isFinalState()<<"  ";
        cout << "  --> Token: " << Trans->get_token();
        cout << endl;
//        for (auto *it: Trans->get_content()) {
//            cout << " , State " << it->get_id();
//        }
//        cout << endl;
    }
}