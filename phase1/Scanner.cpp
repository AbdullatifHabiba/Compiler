#include "Scanner.h"
#include "NFA.h"
#include <iostream>
#include <fstream>
#include <utility>
#include <bits/stdc++.h>

using namespace std;
vector<char *> words;

NFA* Scanner::scan(string pFile) {
    this->file = std::move(pFile);
    return getWords();
}

Scanner::~Scanner() = default;

Scanner::Scanner() {
    keywords = nullptr;
    punctuation = nullptr;
    finalNFA = nullptr;

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
            cout<<"handleKeywords : "<< line<<endl;
            handleKeywords(line);
        } else if (line[0] == '[')             // punctuation
        {
            cout<<"handlePunctuation :"<< line<<endl;

            handlePunctuation(line);
        } else {
            for (int i = 0; i < (int) line.size(); ++i) {
                if (line[i] == ':')          // regular expression
                {
                    cout<<"regular expression :"<< line<<endl;
                    handleExpression(line, i);
                    break;
                } else if (line[i] == '=')     // regular Definition
                {
                    cout<<"regular Definition :"<< line<<endl;
                    handleDefinition(line, i);
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




void Scanner::handleKeywords(string &input) {
    NFA *currentKeyword ;

    for (int i = 1; i < (int) input.size(); ++i) {
        if (input[i] == ' ' or input[i] == '}') continue;

        string token;

        while (input[i] != ' ' and input[i] != '}') token += input[i++];

        currentKeyword = new NFA();
        currentKeyword->start_state = new NFA_State(false);
        currentKeyword->accept_state = new NFA_State(false);
        currentKeyword->accept_state->set_token("keyword");
        currentKeyword->accept_state->set_priority(0);
        currentKeyword->start_state->addTransition(token[0], currentKeyword->accept_state);

        for (int ind = 1; ind < (int) token.size(); ++ind)
            currentKeyword->extend(token[ind]);



        if (keywords == nullptr) keywords = currentKeyword;
        else keywords->OR(currentKeyword);
    }
}

void Scanner::handlePunctuation(string &input) {
    NFA *currentPunctuation ;

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
        currentPunctuation->accept_state->set_token("punctuation");
        currentPunctuation->accept_state->set_priority(1);
        currentPunctuation->start_state->addTransition(token[0], currentPunctuation->accept_state);

        if (punctuation == nullptr) punctuation = currentPunctuation;
        else punctuation->OR(currentPunctuation);
    }
}

void Scanner::handleExpression(string &input, int &i) {
    string expression = input.substr(0, i);

    int k = ++i;
    string token =  input.substr(0,i-1);
    string finalExpression;
    for (; i < (int) input.size(); ++i) {
        if (input[i] == ' ') {
            if (i - 1 >= k) {
                string x = input.substr(k, i - k);
                if (definitions.find(x) != definitions.end())
                    finalExpression += "(" + definitions[x] + ")";
                else
                    finalExpression += x;
            }

            k = i + 1;
        } else if (input[i] == '(' or input[i] == '*' or input[i] == '+' or input[i] == ')' or input[i] == '-' or
                   input[i] == '|') {
            if (i and input[i - 1] == '\\') continue;

            if (i - 1 >= k) {
                string x = input.substr(k, i - k);
                if (definitions.find(x) != definitions.end())
                    finalExpression += "(" + definitions[x] + ")";
                else
                    finalExpression += x;
            }

            finalExpression += input[i];
            k = i + 1;
        }
    }

    if (i > k) {
        string x = input.substr(k, i - k);
        if (definitions.find(x) != definitions.end())
            finalExpression += "(" + definitions[x] + ")";
        else
            finalExpression += x;
    }

    vector<string> tokens = getTokens(finalExpression);
    vector<string> expressionPost = createPostfix(tokens);


    NFA *NFAExpression = (new NFA())->buildNFA(expressionPost);

    NFAExpression->accept_state->setFinalState(true);
    NFAExpression->accept_state->set_token(token);
    NFAExpression->accept_state->set_priority(2);

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
                if (definitions.find(x) != definitions.end())
                    result.push_back("(" + definitions[x] + ")");
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
        if (definitions.find(x) != definitions.end())
            result.push_back("(" + definitions[x] + ")");
        else
            result.push_back(x);
    }

    return result;
}

vector<string> Scanner::createPostfix(vector<string> &tokens) {
    vector<string> result;
    string operations = "+-*|()";
    stack<string> s;
    for (int i = 0; i < (int) tokens.size(); ++i) {
        if (i and tokens[i - 1] != "|" and tokens[i - 1] != "(" and tokens[i - 1] != "-" and
            (tokens[i] == "(" or operations.find(tokens[i]) == std::string::npos)) {
            vector<string> temp = handleStack(tokens, s, operations, i);
            result.insert(result.end(), temp.begin(), temp.end());
        }
        if (tokens[i] == "(" or tokens[i] == "-")
            s.push(tokens[i]);
        else if (tokens[i] == ")") {
            while (!s.empty() && s.top() != "(") {
                result.push_back(s.top());
                s.pop();
            }
            if (!s.empty()) s.pop();
        } else if (tokens[i] == "*") {
            while (!s.empty() && s.top() == "-") {
                result.push_back(s.top());
                s.pop();
            }
            s.push(tokens[i]);
        } else if (tokens[i] == "+") {
            while (!s.empty() && (s.top() == "*" or s.top() == "-")) {
                result.push_back(s.top());
                s.pop();
            }
            s.push(tokens[i]);
        } else if (tokens[i] == "|") {
            while (!s.empty() && (s.top() == "*" or s.top() == "-" or s.top() == "+" or s.top() == " ")) {
                result.push_back(s.top());
                s.pop();
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
vector<string> Scanner::handleStack(vector<string> &tokens, stack<string> &s, string &operations, int i) {
    vector<string> result;
    while (!s.empty()) {
        if (s.top() == "*" or s.top() == "+" or s.top() == "-") {
            result.push_back(s.top());
            s.pop();
        } else break;
    }
    s.emplace(" ");
    return result;
}




void Scanner::handleDefinition(string &input, int &i) {
    string finalIdentifier;
    int z = i;

    while (input[z - 1] == ' ') --z;

    string id = input.substr(0, z);
    int k = ++i;

    for (; i < (int) input.size(); ++i) {
        if (input[i] == ' ') {
            if (i - 1 >= k) {
                string x = input.substr(k, i - k);
                if (definitions.find(x) != definitions.end())
                    finalIdentifier += "(" + definitions[x] + ")";
                else
                    finalIdentifier += x;
            }

            k = i + 1;
        } else if (input[i] == '(' or input[i] == '*' or input[i] == '+' or input[i] == ')' or input[i] == '-' or
                   input[i] == '|') {
            if (i and input[i - 1] == '\\') continue;

            if (i - 1 >= k) {
                string x = input.substr(k, i - k);
                if (definitions.find(x) != definitions.end())
                    finalIdentifier += "(" + definitions[x] + ")";

                else
                    finalIdentifier += x;
            }

            finalIdentifier += input[i];
            k = i + 1;
        }
    }

    if (i > k)
        finalIdentifier += input.substr(k, i - k);

    definitions[id] = finalIdentifier;
}

NFA *Scanner::getFinalNFA() {
    return this->finalNFA;
}

