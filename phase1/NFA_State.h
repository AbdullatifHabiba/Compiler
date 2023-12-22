

#ifndef COMPILERS_NFA_STATE_H
#define COMPILERS_NFA_STATE_H
#include <map>
#include <vector>
#include <string>

using namespace std;

class NFA_State {
public:
    explicit NFA_State( bool isFinal_);
    ~NFA_State();
    void addTransition(char rule, NFA_State *next_state);
    [[nodiscard]] bool isFinalState() const ;
    void setFinalState(bool isFinal);
    map<char, vector<NFA_State*>> getTransitions();
    void set_id(int a);
    [[nodiscard]] int get_id() const;
    void set_priority(int p);
    [[nodiscard]] int get_priority() const;
    void set_token(string t);
    string get_token();


private:
    bool isFinal;
    int priority{};
    string token;
    int id;
    static int increase_id;
    map<char, vector<NFA_State*>> transitions;
};


#endif //COMPILERS_NFA_STATE_H
