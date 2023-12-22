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
    explicit DFA_State(bool is_accepted);

    explicit DFA_State(int id);

    virtual ~DFA_State();

    void set_content(const set<NFA_State*>& content1);
    [[nodiscard]] int get_id() const;
    string get_token();
    [[nodiscard]] bool isFinalState() const;
    DFA_State* get_next(char input);
    set<NFA_State*> get_content();
    void addTransition(char ch, DFA_State *state);

    void set_priority(bool flag, NFA_State *temp);
    void set_token(string s);
    void set_final(bool f);
    void set_priority(int priority1);
    [[nodiscard]] int get_priority() const;
    std::map<char,DFA_State*> transactions;
    [[nodiscard]] map<char, DFA_State *> getTransitions() const ;

private:

    int id{};
    string token;
    set<NFA_State*> content;
    bool isFinal{};
    int priority{};
    static int increase_id;
    static int min_increase_id;
};

#endif