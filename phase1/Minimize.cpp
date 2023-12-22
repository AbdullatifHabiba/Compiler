
#include "Minimize.h"
#include <bits/stdc++.h>
#include "DFA_State.h"
using namespace std;


Minimize::Minimize()= default;
Minimize::~Minimize()= default;

set<DFA_State*> Minimize::minimize_dfa_states(const set<DFA_State*>& DFA) {
    set<DFA_State*> result;
    set<DFA_State*> marked;
    set<char> alpha;
    vector < set < DFA_State* > > grouping[2];

    // Step 1: Perform BFS and get groups
    grouping[0].resize(1);
    result = bfsAndGetGroups(DFA, marked, alpha, grouping);

    // Step 2: Grouping
    create_grouping(0, grouping, alpha);

    // Step 3: Build the minimized DFA
    result = buildMinimizedDFA(grouping, alpha);

    return result;
}
// function to make breadth first search
set<DFA_State*> Minimize::bfsAndGetGroups(const set<DFA_State*>& DFA, set<DFA_State*>& marked, set<char>& alpha, vector<set<DFA_State *>> *grouping) {
    set<DFA_State*> result;

    queue<DFA_State*> q;
    auto start = DFA.begin();
    q.push(*start);
    marked.insert(*start);

    while (!q.empty()) {
        DFA_State* temp = q.front();
        q.pop();

        if (temp->isFinalState()) {
            bool flag = false;
            for (int i = 1; i < static_cast<int>(grouping[0].size()); i++) {
                auto it = grouping[0][i].begin();
                if ((*it)->get_token() == temp->get_token()) {
                    grouping[0][i].insert(temp);
                    flag = true;
                    break;
                }
            }
            if (!flag) {
                set<DFA_State*> new_set;
                new_set.insert(temp);
                grouping[0].push_back(new_set);
            }
        } else {
            grouping[0][0].insert(temp);
        }

        for (auto& transaction : temp->transactions) {
            alpha.insert(transaction.first);
            DFA_State* se = transaction.second;
            if (marked.find(se) == marked.end()) {
                marked.insert(se);
                q.push(se);
            }
        }
    }

    return result;
}
// function to make the grouping and partitions
 void Minimize::create_grouping(int bit, vector<set<DFA_State *>> *grouping, set<char>& alpha) {
    while (true) {
        for (int i = 0; i < static_cast<int>(grouping[bit].size()); i++) {
            map<vector<int>, set<DFA_State*>> current;
            for (auto it = grouping[bit][i].begin(); it != grouping[bit][i].end(); it++) {
                vector<int> dest;
                for (char itra : alpha) {
                    DFA_State* d = (*it)->get_next(itra);
                    if (d->get_id() == -1) {
                        dest.push_back(-1);
                    } else {
                        for (int k = 0; k < static_cast<int>(grouping[bit].size()); k++) {
                            if (grouping[bit][k].find(d) != grouping[bit][k].end()) {
                                dest.push_back(k);
                            }
                        }
                    }
                }
                if (current.find(dest) == current.end()) {
                    set<DFA_State*> x;
                    x.insert(*it);
                    current[dest] = x;
                } else {
                    current[dest].insert(*it);
                }
            }

            for (auto& e : current) {
                grouping[bit ^ 1].push_back(e.second);
            }
        }

        if (grouping[0].size() == grouping[1].size()) break;
        grouping[bit].clear();
        bit ^= 1;
    }
}
// function to build the minimized dfa states
set<DFA_State*> Minimize::buildMinimizedDFA(const vector<set<DFA_State*>>*grouping, const set<char>& alpha) {
    set<DFA_State*> result;
    int start_index;
    bool flag = false;

    vector<DFA_State*> new_st;
    for (int i = 0; i < static_cast<int>(grouping[1].size()); i++) {
        auto* st = new DFA_State(i);
        new_st.push_back(st);
    }

    for (int i = 0; i < static_cast<int>(grouping[0].size()); i++) {
        for (auto it = grouping[0][i].begin(); it != grouping[0][i].end(); it++) {
            if ((*it)->get_id() == 0) {
                start_index = i;
                new_st[0]->set_final((*it)->isFinalState());
                new_st[0]->set_token((*it)->get_token());
                new_st[0]->set_priority((*it)->get_priority());

                for (auto x = (*it)->transactions.begin(); x != (*it)->transactions.end(); x++) {
                    DFA_State* y = (*it)->get_next(x->first);
                    for (int k = 0; k < static_cast<int>(grouping[0].size()); k++) {
                        if (grouping[0][k].find(y) != grouping[0][k].end()) {
                            if (start_index == k) {
                                new_st[0]->addTransition(x->first, new_st[0]);
                            } else if (start_index != k && k < start_index) {
                                new_st[0]->addTransition(x->first, new_st[k + 1]);
                            } else if (start_index != k && k > start_index) {
                                new_st[0]->addTransition(x->first, new_st[k]);
                            }
                        }
                    }
                }
                flag = true;
                break;
            }
        }
        if (flag) break;
    }

    for (int i = 0; i < static_cast<int>(grouping[0].size()); i++) {
        if (i == start_index) continue;
        auto it = grouping[0][i].begin();
        int ind;
        if (start_index < i) {
            ind = i;
        } else {
            ind = i + 1;
        }

        new_st[ind]->set_final((*it)->isFinalState());
        new_st[ind]->set_token((*it)->get_token());
        new_st[ind]->set_priority((*it)->get_priority());

        for (auto x = (*it)->transactions.begin(); x != (*it)->transactions.end(); x++) {
            DFA_State* y = (*it)->get_next(x->first);
            for (int k = 0; k < static_cast<int>(grouping[0].size()); k++) {
                if (grouping[0][k].find(y) != grouping[0][k].end()) {
                    if (start_index == k) {
                        new_st[ind]->addTransition(x->first, new_st[0]);
                    } else if (start_index != k && k < start_index) {
                        new_st[ind]->addTransition(x->first, new_st[k + 1]);
                    } else if (start_index != k && k > start_index) {
                        new_st[ind]->addTransition(x->first, new_st[k]);
                    }
                }
            }
        }
    }

    for (auto i : new_st) {

        if (i->get_id() == 0) {
            this->start_state = i;
        }
        result.insert(i);
    }

    return result;
}


bool check_Keywords_letters(char ch){

    return ch=='i' || ch=='f'|| ch=='b' || ch == 'e'||ch=='w';
}
/*
void Minimize::printMinGraph(const set<DFA_State*>& Mfa)
{
    // declare the output file
    ofstream out("graph.dot");
    cout << "the graph of the DFA is " << Mfa.size() << endl;
    out << "digraph finite_state_machine {\n";
    out << "rankdir=LR;\n";
    //out << "size=\"30,30\"\n";
    out << "node [shape = circle];\n";

    // Create a map to store transitions with their labels
    map<pair<int, int>, string> transitions;

    for (auto state : Mfa)
    {
        // If the state is final, make it a double circle
        if (state->isFinalState())
            out << state->get_id() << " [shape = doublecircle, style=filled, fillcolor=green];\n";

        for (auto trs : state->getTransitions())
        {
            // Use a pair of source state ID and target state ID as the key
            pair<int, int> key = make_pair(state->get_id(), trs.second->get_id());

            // Append the label to the existing labels for this transition
            if (transitions.count(key) > 0)
            {
                transitions[key] += ", " + string(1, trs.first);
            }
            else
            {
                transitions[key] = string(1, trs.first);
            }
        }
    }

    // Print the transitions
    for (const auto& trs : transitions)
    {
        out << trs.first.first << " -> " << trs.first.second;
        out << " [ label = \"" << trs.second << "\" ];\n";
    }

    out << "}\n";
    out.close();
}*/
void Minimize::printMinGraph(const set<DFA_State*>& Mfa)
{
    // declare the output file
    ofstream out("graph.dot");
    cout<<"build graph of the Min DFA  "<<endl;
    out << "digraph finite_state_machine {\n";
    out << "rankdir=LR;\n";
    //out << "size=\"30,30\"\n";
    out << "node [shape = circle];\n";


    // Create a map to store transitions with their labels
    map<pair<int, int>, string> transitions;

    for(auto state : Mfa)
    {
        // If the state is final, make it a double circle
        if (state->isFinalState())
            out << state->get_id() << " [shape = doublecircle, style=filled, fillcolor=green];\n";

        for(auto trs: state->getTransitions())
        {
            // Use a pair of source state ID and target state ID as the key
            pair<int, int> key = make_pair(state->get_id(), trs.second->get_id());

            // Append the label to the existing labels for this transition
            if (transitions.count(key) > 0)
            {
                // Check if the transition is a letter or a digit and not in keywords_start_letter
                if ((isalpha(trs.first) &&!check_Keywords_letters(trs.first)) && transitions[key].find("letter") == string::npos)
                    transitions[key] += ", letter";
                else if (isdigit(trs.first) && transitions[key].find("digit") == string::npos)
                    transitions[key] += ", digit";

                else if ((!isalpha(trs.first) && !isdigit(trs.first)))
                    transitions[key] += ", " + string(1, trs.first);
                else if(check_Keywords_letters(trs.first))
                    transitions[key] += ", " + string(1, trs.first);


            }
            else
            {
                if (isalpha(trs.first)&&!check_Keywords_letters(trs.first))
                    transitions[key] = "letter";
                else if (isdigit(trs.first))
                    transitions[key] = "digit";
                else
                    transitions[key] = string(1, trs.first);
            }
        }
    }

    // Print the transitions
    for (const auto& trs : transitions)
    {
        out << trs.first.first << " -> " << trs.first.second;
        out << " [ label = \"" << trs.second << "\" ];\n";
    }

    out << "}\n";
    out.close();
}


DFA_State *Minimize::get_start_state() const {
    return this->start_state;
}
