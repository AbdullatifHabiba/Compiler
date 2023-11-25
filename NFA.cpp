//
// Created by abdu on 11/25/23.
//

#include <stack>
#include "NFA.h"
#include "NFA_State.h"
#include <iostream>
#include <regex>
#include <set>

using namespace std;
void NFA::printNFA() {
    cout << "NFA" << endl;
    // print from start state
    cout << "Start State: " << start_state << endl;
    cout << "Accept State: " << accept_state << endl;
    cout << "Transitions: " << endl;
    for (auto& state : states) {
        cout << state << endl;
        for (auto& transition : state->getTransitions()) {
            cout << "\t" << transition.first << ": ";
            for (auto& next_state : transition.second) {
                cout << next_state << " ";
            }
            cout << endl;
        }
    }


}
void NFA::buildNFA(std::vector<char *> vector1) {
    std::stack<NFA_State*> nfaStack;

    for (auto& rule : vector1) {
        if (isOperand(*rule)) {
            NFA_State* operand1 = new NFA_State();
            NFA_State* operand2 = new NFA_State();
            operand1->addTransition(*rule, operand2);
            nfaStack.push(operand1);
        } else {
            NFA_State* result = new NFA_State();
            if (*rule == '*') {
                NFA_State* nfa = nfaStack.top(); nfaStack.pop();
                result->addEpsilonTransition(nfa);
                nfa->getTransitions()[EPSILON].back()->addEpsilonTransition(result);
            } else if (*rule == '|') {
                NFA_State* nfa2 = nfaStack.top(); nfaStack.pop();
                NFA_State* nfa1 = nfaStack.top(); nfaStack.pop();
                result->addEpsilonTransition(nfa1);
                result->addEpsilonTransition(nfa2);
                nfa1->getTransitions()[EPSILON].back()->addEpsilonTransition(result);
                nfa2->getTransitions()[EPSILON].back()->addEpsilonTransition(result);
            } else if (*rule == '.') {
                NFA_State* nfa2 = nfaStack.top(); nfaStack.pop();
                NFA_State* nfa1 = nfaStack.top(); nfaStack.pop();
                nfa1->getTransitions()[EPSILON].back()->addEpsilonTransition(nfa2);
                result = nfa1;
            }
            nfaStack.push(result);
        }
    }

    // The final NFA is on top of the stack
    NFA_State* nfa = nfaStack.top();
    nfaStack.pop();
    start_state = nfa;
}



NFA::~NFA() = default;

NFA::NFA() = default;
bool isIdentifier(const std::string& token) {
    // Check if the token matches the pattern for identifiers
    // An identifier is a letter followed by zero or more letters or digits
    std::regex pattern("[a-zA-Z][a-zA-Z0-9]*");
    return std::regex_match(token, pattern);
}

bool isNumber(const std::string& token) {
    // Check if the token matches the pattern for numbers
    // A number is an unsigned integer or a floating-point number
    regex pattern("[0-9]*\\.?[0-9]+([eE][-+]?[0-9]+)?");
    return regex_match(token, pattern);
}

bool isKeyword(const std::string& token) {
    // Check if the token is a keyword
    // The keywords are: int, float, boolean, if, else, while
    set<string> keywords = {"int", "float", "boolean", "if", "else", "while"};
    return keywords.count(token) > 0;
}

bool isOperator(const std::string& token) {
    // Check if the token is an operator
    // The operators are: +, -, *, /, =, <=, <, >, >=, !=, ==
    set<string> operators = {"+", "-", "*", "/", "=", "<=", "<", ">", ">=", "!=", "=="};
    return operators.count(token) > 0;
}

bool isPunctuation(const std::string& token) {
    // Check if the token is a punctuation symbol
    // The punctuation symbols are parentheses, curly brackets, commas and semicolons
    set<string> punctuation = {"(", ")", "{", "}", ",", ";"};
    return punctuation.count(token) > 0;
}

