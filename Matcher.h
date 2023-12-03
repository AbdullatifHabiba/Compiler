//
// Created by abdu on 11/25/23.
//
#ifndef COMPILERS_MATCHER_H
#define COMPILERS_MATCHER_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "NFA_State.h"
#include "DFA_State.h"

class Matcher {
private:
    string out;
    vector<string> transitionTable;
    string output_file_name;

public:
    Matcher();
    ~Matcher();
    void matchFileWithDFA(const string& file_name, DFA_State* start);
    void setOutputFileName(string outputFileName);
    void writeOutputToFile(string name);
    bool runDFA(string str, DFA_State* start);
    vector<string> getTransitionTable();
};


#endif //COMPILERS_MATCHER_H

