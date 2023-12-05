//
// Created by u s e r on 03/12/2023.
//

#ifndef COMPILERS_MINIMIZE_H
#define COMPILERS_MINIMIZE_H

#include <bits/stdc++.h>
#include "DFA_State.h"
using namespace std;

class Minimize
{
public:
    Minimize();
    virtual ~Minimize();
    static set<DFA_State*> DFA_min (const set<DFA_State*>& DFA);

protected:

private:
};

#endif //COMPILERS_MINIMIZE_H










