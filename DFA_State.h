//
// Created by abdu on 11/25/23.
//

#ifndef COMPILERS_DFA_STATE_H
#define COMPILERS_DFA_STATE_H


#include <set>
#include "NFA_State.h"

class DFA_State {
private:
    static int increase_id;
    set<NFA_State *> content;
    int priority{};
    bool isFinal{};
    string token;
    int id;
public:
    ~DFA_State();
    DFA_State();


    map<char, DFA_State*> transactions;

    [[nodiscard]] int get_id() const;
    set<NFA_State *> get_content();
    string get_token();
    [[nodiscard]] bool isFinalState() const;
    DFA_State *get_next(char input);
    void set_content(const set<NFA_State *>& Content);
    void addTransition(char ch, DFA_State *state);
    [[nodiscard]] map<char, DFA_State *> getTransitions() const;

    void set_priority(bool flag, NFA_State *temp);
};

#endif //COMPILERS_DFA_STATE_H
