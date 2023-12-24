//
// Created by Hardware on 12/23/2023.
//

#ifndef COMPILERS_LL1_GENERATOR_H
#define COMPILERS_LL1_GENERATOR_H

#include <string>
#include <vector>
#include <map>
#include "Token.h"
#include "CFGRule.h"
using namespace std;

#endif //COMPILERS_LL1_GENERATOR_H
class LL1_Generator{
public:
    static void LR_Elimination(map<string, CFGRule *>& LR_map);
    static void LF_Elimination(map<string, CFGRule *> &cfg);
    void NonImmediate_LR_Elimination(map<string, CFGRule *> &cfg , vector<string> nonTerminals);
};