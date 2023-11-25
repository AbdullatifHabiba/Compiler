#include "Scanner.h"
#include <iostream>
#include <fstream>
#include <cstring>
#include <bits/stdc++.h>
using namespace std;
vector<char *> words;
void Scanner::scan(string pFile) {
    this->file = pFile;
    getWords();
}

Scanner::~Scanner() = default;

Scanner::Scanner() = default;

void Scanner::getWords() {
    fstream is;
    // check if file exists
    is.open(this->file, ios::in);
    if (!is) {
        cout << "File not found" << endl;
        return;
    }
    cout << "Reading from the file " << file <<endl;
    string line;
    while (getline(is, line)) {
        cout << line << endl;
        splitInput(line);
    }
}

void Scanner::splitInput(const std::string &line) {
    std::istringstream iss(line);
    std::string word;

    while (iss >> word) {
        char *cstr = new char[word.length() + 1];
        strcpy(cstr, word.c_str());
        words.push_back(cstr);
    }
}

std::vector<char *> Scanner::readInput() {
    return words;
}
