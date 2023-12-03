//
// Created by abdu on 11/25/23.
//

#include "DFA.h"
#include <queue>
#include <iostream>

DFA::DFA() = default;

DFA::~DFA() = default;

set<NFA_State *> Mapped;

//    std::cout << "State: " << s->get_id() <<" : "<<endl;
// get each nfa state epsilon closure
void DFA::e_closure(NFA_State *s) {
    if (Mapped.find(s) != Mapped.end()) {
        return;
    }

    set<NFA_State *> v;
    auto transitions = s->getTransitions()['@'];
    for (NFA_State *x: transitions) {
        v.insert(x);
    }
    Mapped.insert(s);
    if (v.size() == 0) {
        return;
    }
    for (auto state : v) {
        e_closure(state);
    }
}

set<NFA_State *> DFA::e_closure(set<NFA_State *> T) {
    set<NFA_State *> returned_set;
    for (auto state : T) {
        Mapped.clear();
        e_closure(state);
        set<NFA_State *> s = Mapped;
        returned_set.insert(s.begin(), s.end());
    }
    return returned_set;
}

set<NFA_State *> DFA::move(set<NFA_State *> T, char input) {
    set<NFA_State *> returned_set;
    for (auto state : T) {
        set<NFA_State *> s1;
        auto transitions = state->getTransitions()[input];
        for (NFA_State *x: transitions) {
            s1.insert(x);
        }
        set<NFA_State *> s2 = e_closure(s1);
        returned_set.insert(s2.begin(), s2.end());
    }
    return returned_set;
}

set<DFA_State *> DFA::convert_NFA_to_DFA(NFA_State *start) {
cout << "start convert NFA to DFA" << endl;
    queue<DFA_State *> unmarked;      /*queue to add unmarked new D_states*/
    set<DFA_State *> DFA;              /*returned DFA graphe*/
    Mapped.clear();
    e_closure(start);
cout << "after closure" << endl;
    auto *s = new DFA_State();
    s->set_content(Mapped);
    DFA.insert(s);
    unmarked.push(s);
    cout << "after insert" << endl;
    set<char> alpha = get_alpha(start);
    while (!unmarked.empty()) {
        DFA_State *temp = unmarked.front();
        unmarked.pop();

        /*loop for all inputs on set alpha*/
        for (char it : alpha) {
            /*get destination from source temp on input it */
            set<NFA_State *> destination = move(temp->get_content(), it);


            /*chech if the dest is not in DFA*/
            bool flag = false;
            DFA_State *test;
            for (auto d : DFA) {
                if (d->get_content() == destination) {
                    flag = true;
                    test = d;
                    break;

                }
            }

            if (!flag) {
                auto *dest = new DFA_State();
                dest->set_content(destination);
                DFA.insert(dest);
                unmarked.push(dest);
                // cout << "rererere :::: " << dest -> get_name() << endl;
                temp->addTransition(it, dest);
            } else {
                temp->addTransition(it, test);
            }
        }
    }
    return DFA;
}

set<char> DFA::get_alpha(NFA_State *S) {
    set<char> alpha;

    queue<NFA_State *> current;
    set<NFA_State *> visited;

    current.push(S);
    visited.insert(S);

    while (!current.empty()) {
        NFA_State *x = current.front();
        current.pop();
        auto transitions = x->getTransitions();
        for (auto it = transitions.begin(); it != transitions.end(); ++it) {
            alpha.insert(it->first);

            for (NFA_State *n: it->second) {
                if (n != nullptr && visited.find(n) == visited.end()) {
                    visited.insert(n);
                    current.push(n);
                }
            }
        }

    }
    alpha.erase('@');
    alpha.erase('\0');
    for (auto it = alpha.begin(); it != alpha.end(); ++it) {
        //  cout << *it << "  ";
    }
    return alpha;
}

void DFA::printDFA(set<DFA_State *> DFA) {
    for (auto element: DFA) {
        cout << "State" << element->get_id();
        for (auto j: element->get_content())
            cout << " State :" << j->get_id();
        if (element->isFinalState() == 0)
            cout << " <<<<<<<---- not final " << endl;
        else
            cout << " ---->>>>>> Final" << endl;
        for (auto i: element->getTransitions()) {
            cout << "----->> " << i.first << " >>----- ";
            cout << "State " << i.second->get_id() << endl;
        }
    }
}
