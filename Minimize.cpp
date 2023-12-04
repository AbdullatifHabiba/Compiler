//
// Created by u s e r on 03/12/2023.
//

#include "Minimize.h"
#include <bits/stdc++.h>
#include "DFA_State.h"
using namespace std;


Minimize::Minimize(){}
Minimize::~Minimize(){}

set<DFA_State*> Minimize:: DFA_min (set<DFA_State*> DFA){
//    initialize some variables
    vector < set < DFA_State* > > grouping[2];
    //group[0][0]--> non acceptance, group[0][i]--> acceptance for different states
    set <DFA_State*> result;
    set < char > alpha;
    grouping[0].resize(1);
    queue < DFA_State* > q;
    set<DFA_State*>::iterator start = DFA.begin();
    q.push(*start);
    set < DFA_State* > marked;
    marked.insert(*start);

// Breadth First Search to get all states in its group
    while(!q.empty())
    {
        DFA_State* temp = q.front();
        q.pop();
        // if temp is an acceptance state then insert it
        // in the group corresponding to its name
        if (temp -> isFinalState())
        {
            //if the group is present then insert in it, else create new set
            bool flag = false;
            for (int i = 1 ; i < (int) grouping[0].size() ; i++)
            {
                set<DFA_State*>::iterator it = grouping[0][i].begin();
                if ( (*it) -> get_token() == temp -> get_token())
                {
                    grouping[0][i].insert(temp);
                    flag = true;
                    break;
                }
            }
            if (!flag)
            {
                set<DFA_State*> new_set;
                new_set.insert(temp);
                grouping[0].push_back(new_set);
            }
        }
            // if temp is Non acceptance state then add it to group [0][0]
        else
        {
            grouping[0][0].insert(temp);
        }
        //if the next state is not marked before then mark it and push it to stack
        typedef map<char, DFA_State* > :: const_iterator MapIterator;
        for (MapIterator it = temp -> transactions.begin(); it != temp -> transactions.end(); it++)
        {
            alpha.insert(it -> first);
            DFA_State* se = it->second;
            if (marked.find(se) == marked.end())
            {
                marked.insert(se);
                q.push(se);
            }

        }
    }
//Now we have the states each in its corresponding group

// let's make the Minimization for each group
    int bit = 0;
    while (true)
    {
        for (int i = 0 ; i < (int) grouping[bit].size() ; i++)
        {
            map < vector < int >, set < DFA_State* > > current;
            // for each state in the group
            for (set<DFA_State*>::iterator it = grouping[bit][i].begin(); it != grouping[bit][i].end(); it++)
            {
                vector < int > dest;
                // for all alphabet in each state
                for (set<char>::iterator itra = alpha.begin() ; itra != alpha.end() ; itra++)
                {
                    DFA_State* d = (*it) -> get_next((*itra));
                    if (d -> get_id() == -1) dest.push_back(-1); //dead state
                    else
                    {
                        for (int k = 0 ; k < (int) grouping[bit].size() ; k++)
                        {
                            if (grouping[bit][k].find(d) != grouping[bit][k].end())
                            {
                                dest.push_back(k);
                            }
                        }
                    }
                }
                //after get all transitions, add destinations to current
                if (current.find(dest) == current.end())
                {
                    set <DFA_State*> x;
                    x.insert(*it);
                    current[dest] = x;
                }
                else
                {
                    current[dest].insert(*it);
                }
            }

            typedef  map < vector < int >, set < DFA_State* > > :: const_iterator MapIterator;
            for (MapIterator e = current.begin(); e != current.end(); e++)
            {
                grouping[bit ^ 1].push_back(e -> second);
            }
        }

        if (grouping[0].size() == grouping[1].size()) break;
        grouping[bit].clear();
        bit ^= 1;

    }

    //after partitioning into group now make new DFA with the new groups

    /*finding starting state*/
    int start_index ;
    bool flag = false;
    //push empty states to new_st with number of all groups in the DFA
    vector < DFA_State* > new_st ;
    for (int i = 0 ; i < (int) grouping[0].size() ; i++)
    {
        DFA_State* st = new DFA_State();
        new_st.push_back(st);
    }

    //we want to enforce group contain start state to be at index=0
    // for each group in the DFA
    for (int i = 0 ; i < (int) grouping[0].size() ; i++)
    {
        for (set<DFA_State*>::iterator it = grouping[0][i].begin(); it != grouping[0][i].end(); it++)
        {
            if( (*it) -> get_id() == 0) //start state
            {
                start_index = i;
                new_st[0] -> set_content((*it) -> get_content());
//                new_st[0]-> set_final((*it) -> isFinalState());
//                new_st[0]-> set_token((*it) -> get_token());
                typedef map<char, DFA_State* > :: const_iterator MapIterator;
                for (MapIterator x = (*it) -> transactions.begin(); x != (*it) -> transactions.end(); x++)
                {   //get next state
                    DFA_State* y = (*it) -> get_next(x -> first);
                    for (int k = 0 ; k < (int) grouping[0].size() ; k++)
                    {//search for this state in the groups
                        if (grouping[0][k].find(y) != grouping[0][k].end())
                        {
                            if (start_index == k) //self loop
                            {
                                new_st[0] -> addTransition(x -> first, new_st[0]);
                            }
                                //if k<start index then start state will be zero, and then we will shift th states before
                                //so that transition will be k+1
                            else if (start_index != k && k < start_index)
                            {
                                new_st[0] -> addTransition(x -> first, new_st[k+1]);
                            }
                            else if (start_index != k && k > start_index)
                            {
                                new_st[0] -> addTransition(x -> first, new_st[k]);
                            }
                        }
                    }

                }

                flag = true;
                break;
            }
        }
        if (flag)break;
    }




    /*for any state except start state*/

    for (int i = 0 ; i < (int) grouping[0].size() ; i++)
    {
        if (i == start_index)continue;
        set<DFA_State*>::iterator it = grouping[0][i].begin();
        int ind;
        if (start_index < i ) {ind = i;}
        else {ind = i+1;}

        new_st[ind] -> set_content((*it) -> get_content());
//        new_st[ind] -> set_final((*it) -> isFinalState());
//        new_st[ind] -> set_token((*it) -> get_token());
        typedef map<char, DFA_State* > :: const_iterator MapIterator;
        for (MapIterator x = (*it) -> transactions.begin(); x != (*it) -> transactions.end(); x++)
        {
            DFA_State* y = (*it) -> get_next(x -> first);

            for (int k = 0 ; k < (int) grouping[0].size() ; k++)
            {
                if (grouping[0][k].find(y) != grouping[0][k].end())
                {
                    if (start_index == k)
                    {
                        new_st[ind] -> addTransition(x -> first, new_st[0]);
                    }
                    else if (start_index != k && k < start_index)
                    {
                        new_st[ind] -> addTransition(x -> first, new_st[k+1]);
                    }
                    else if (start_index != k && k > start_index)
                    {
                        new_st[ind] -> addTransition(x -> first, new_st[k]);
                    }
                }
            }

        }
    }

    for (int i = 0 ; i < (int) grouping[0].size() ; i++)
    {
        cout << "here ---> " << i << "content";
        for (set<DFA_State*>::iterator it = grouping[0][i].begin(); it != grouping[0][i].end(); it++)
        {
            cout << (*it) -> get_id() << ' ';
        }
        cout << endl;
    }

    for (int i = 0 ; i < (int) new_st.size() ; i++)
    {
        result.insert(new_st[i]);
    }

    return result;
}
