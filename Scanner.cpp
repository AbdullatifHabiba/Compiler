#include "Scanner.h"
#include "NFA.h"
#include <iostream>
#include <fstream>
#include <cstring>
#include <bits/stdc++.h>

using namespace std;
vector<char *> words;

NFA* Scanner::scan(string pFile) {
    this->file = pFile;
    return getWords();
}

Scanner::~Scanner() = default;

Scanner::Scanner() {
    keywords = nullptr;
    punctuation = nullptr;
    finalNFA = nullptr;
    tokenTypes = {"Keyword", "Punctuation"};

}

NFA *Scanner::getWords() {
    fstream is;
    // check if file exists
    is.open(this->file, ios::in);
    if (!is) {
        cout << "File not found" << endl;
        return nullptr;
    }
    cout << "Reading from the file " << file << endl;
    string line;
    while (getline(is, line)) {
        if (line[0] == '{')                  // keyword
        {
            parseKeyword(line);
        } else if (line[0] == '[')             // punctuation
        {
            parsePunctuation(line);
        } else {
            for (int i = 0; i < (int) line.size(); ++i) {
                if (line[i] == ':')          // regular expression
                {
                    parseExpression(line, i);
                    break;
                } else if (line[i] == '=')     // regular Definition
                {
                    parseDefinition(line, i);
                    break;
                }
            }
        }
    }
    if (keywords != nullptr) {
        keywords->accept_state->setFinalState(true);


        if (finalNFA == nullptr)
            finalNFA = keywords;
        else
            finalNFA->join(keywords);
    }

    if (punctuation != nullptr) {
        punctuation->accept_state->setFinalState(true);


        if (finalNFA == nullptr)
            finalNFA = punctuation;
        else
            finalNFA->join(punctuation);
    }
   cout << "NFA is built successfully" << endl;
    return finalNFA;
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


void Scanner::parseKeyword(string &input) {
    NFA *currentKeyword = nullptr;

    for (int i = 1; i < (int) input.size(); ++i) {
        if (input[i] == ' ' or input[i] == '}') continue;

        string token;

        while (input[i] != ' ' and input[i] != '}') token += input[i++];

        currentKeyword = new NFA();
        currentKeyword->start_state = new NFA_State(false);
        currentKeyword->accept_state = new NFA_State(false);
        currentKeyword->start_state->addTransition(token[0], currentKeyword->accept_state);

        for (int i = 1; i < (int) token.size(); ++i)
            currentKeyword->extend(token[i]);


        if (keywords == nullptr) keywords = currentKeyword;
        else keywords->OR(currentKeyword);
    }
}

void Scanner::parsePunctuation(string &input) {
    NFA *currentPunctuation = nullptr;

    for (int i = 1; i < (int) input.size(); ++i) {
        if (input[i] == ' ' or input[i] == ']') continue;

        std::string token;
        if (input[i] == '\\')
            token += input[++i];
        else
            token += input[i];

        assert(token.size() == 1);

        currentPunctuation = new NFA();
        currentPunctuation->start_state = new NFA_State(false);
        currentPunctuation->accept_state = new NFA_State(false);
        currentPunctuation->start_state->addTransition(token[0], currentPunctuation->accept_state);

        if (punctuation == nullptr) punctuation = currentPunctuation;
        else punctuation->OR(currentPunctuation);
    }
}

void Scanner::parseExpression(string &input, int &i) {
    string expression = input.substr(0, i);

    int k = ++i;

    string finalExpression;
    for (; i < (int) input.size(); ++i) {
        if (input[i] == ' ') {
            if (i - 1 >= k) {
                string x = input.substr(k, i - k);
                if (identifiers.find(x) != identifiers.end())
                    finalExpression += "(" + identifiers[x] + ")";
                else
                    finalExpression += x;
            }

            k = i + 1;
        } else if (input[i] == '(' or input[i] == '*' or input[i] == '+' or input[i] == ')' or input[i] == '-' or
                   input[i] == '|') {
            if (i and input[i - 1] == '\\') continue;

            if (i - 1 >= k) {
                string x = input.substr(k, i - k);
                if (identifiers.find(x) != identifiers.end())
                    finalExpression += "(" + identifiers[x] + ")";
                else
                    finalExpression += x;
            }

            finalExpression += input[i];
            k = i + 1;
        }
    }

    if (i > k) {
        string x = input.substr(k, i - k);
        if (identifiers.find(x) != identifiers.end())
            finalExpression += "(" + identifiers[x] + ")";
        else
            finalExpression += x;
    }

    vector<string> tokens = getTokens(finalExpression);

    vector<string> expressionPost = generatePostfix(tokens);

    NFA *NFAExpression = (new NFA())->buildNFA(expressionPost);

    NFAExpression->accept_state->setFinalState(true);

    if (finalNFA == nullptr) finalNFA = NFAExpression;
    else finalNFA->join(NFAExpression);
}

vector<string> Scanner::getTokens(string &input) {
    vector<string> result;

    int k = 0;
    int i = 0;
    for (; i < (int) input.size(); ++i) {
        if (input[i] == '(' or input[i] == '*' or input[i] == '+' or input[i] == ')' or input[i] == '-' or
            input[i] == '|') {
            if (i and input[i - 1] == '\\') continue;
            if (i - 1 >= k) {
                string x = input.substr(k, i - k);
                if (identifiers.find(x) != identifiers.end())
                    result.push_back("(" + identifiers[x] + ")");
                else
                    result.push_back(x);
            }

            string z;
            z += input[i];
            result.push_back(z);
            k = i + 1;
        }
    }
    if (i > k) {
        string x = input.substr(k, i - k);
        if (identifiers.find(x) != identifiers.end())
            result.push_back("(" + identifiers[x] + ")");
        else
            result.push_back(x);
    }

    return result;
}

vector<string> Scanner::generatePostfix(vector<string> &tokens) {
    vector<string> result;
    string operations = "+-*|()";
    stack<string> s;
    for (int i = 0; i < (int) tokens.size(); ++i) {
        if (i and tokens[i - 1] != "|" and tokens[i - 1] != "(" and tokens[i - 1] != "-" and
            (tokens[i] == "(" or operations.find(tokens[i]) == std::string::npos)) {
            while (!s.empty()) {
                if (s.top() == "*" or s.top() == "+" or s.top() == "-") {
                    result.push_back(s.top());
                    s.pop();
                } else break;
            }
            s.push(" ");
        }
        if (tokens[i] == "(" or tokens[i] == "-")
            s.push(tokens[i]);

        else if (tokens[i] == ")") {
            while (!s.empty()) {
                if (s.top() == "(") {
                    s.pop();
                    break;
                }
                result.push_back(s.top());
                s.pop();
            }
        } else if (tokens[i] == "*") {
            while (!s.empty()) {
                if (s.top() == "-") {
                    result.push_back(s.top());
                    s.pop();
                } else break;
            }
            s.push(tokens[i]);
        } else if (tokens[i] == "+") {
            while (!s.empty()) {
                if (s.top() == "*" or s.top() == "-") {
                    result.push_back(s.top());
                    s.pop();
                } else break;
            }
            s.push(tokens[i]);
        } else if (tokens[i] == "|") {
            while (!s.empty()) {
                if (s.top() == "*" or s.top() == "-" or s.top() == "+" or s.top() == " ") {
                    result.push_back(s.top());
                    s.pop();
                } else break;
            }
            s.push(tokens[i]);
        } else
            result.push_back(tokens[i]);
    }
    while (!s.empty()) {
        result.push_back(s.top());
        s.pop();
    }

    return result;
}

void Scanner::parseDefinition(string &input, int &i) {
    string finalIdentifier;
    int z = i;

    while (input[z - 1] == ' ') --z;

    string id = input.substr(0, z);
    int k = ++i;

    for (; i < (int) input.size(); ++i) {
        if (input[i] == ' ') {
            if (i - 1 >= k) {
                string x = input.substr(k, i - k);
                if (identifiers.find(x) != identifiers.end())
                    finalIdentifier += "(" + identifiers[x] + ")";
                else
                    finalIdentifier += x;
            }

            k = i + 1;
        } else if (input[i] == '(' or input[i] == '*' or input[i] == '+' or input[i] == ')' or input[i] == '-' or
                   input[i] == '|') {
            if (i and input[i - 1] == '\\') continue;

            if (i - 1 >= k) {
                string x = input.substr(k, i - k);
                if (identifiers.find(x) != identifiers.end())
                    finalIdentifier += "(" + identifiers[x] + ")";

                else
                    finalIdentifier += x;
            }

            finalIdentifier += input[i];
            k = i + 1;
        }
    }

    if (i > k)
        finalIdentifier += input.substr(k, i - k);

    identifiers[id] = finalIdentifier;
}

