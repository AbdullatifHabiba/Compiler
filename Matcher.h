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

class Matcher {
public:
    Matcher();
    ~Matcher();

    std::vector<std::string> get_sym_table();
    void set_output_file_name(std::string output_file_name);

    void matchFile(const string &file_name, NFA_State *start);

private:
    std::string output_file_name;
    std::string out;
    std::vector<std::string> symbol_table;

    void write_output_file(std::string name);
    bool run(std::string str, NFA_State* start);

};

#endif //COMPILERS_MATCHER_H

