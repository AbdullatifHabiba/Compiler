#ifndef D_STATE_H
#define D_STATE_H
#include"NFA_State.h"

#include <string>
#include <vector>
#include <map>
#include <set>

using namespace std;

class DFA_State
{
public:
    DFA_State();
    DFA_State(bool is_accepted);
    virtual ~DFA_State();

    void set_content(set<NFA_State*> content);
    int get_id();
    string get_token();
    bool isFinalState();
    DFA_State* get_next(char input);
    set<NFA_State*> get_content();
    void addTransition(char ch, DFA_State *state);
    void set_priority(bool flag, NFA_State *temp);
    void set_token(string s);
    void set_final(bool f);
    /*need it as public*/
    std::map<char,DFA_State*> transactions;
    map<char, DFA_State *> getTransitions() ;

private:

    int id;
    string token;
    set<NFA_State*> content;
    bool isFinal;
    int priority;
    static int increase_id;
    static int min_increase_id;
};

#endif