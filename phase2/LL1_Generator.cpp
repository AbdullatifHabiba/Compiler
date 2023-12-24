//
// Created by Hardware on 12/23/2023.
//
#include <iostream>
#include "LL1_Generator.h"

// Function to perform left factoring elimination on a CFG
void LL1_Generator::LF_Elimination(map<string, CFGRule*>& cfg) {
    // Iterate over each rule in the CFG
    for (auto& rule : cfg) {
        map<string, vector<vector<Token>>> groups;
        // Group the derived strings by their first token
        for (const auto& str : rule.second->getDerivedStrings()) {
            if (!str.empty())
                groups[str[0].getName()].push_back(str);
        }

        // Clear the derived strings of the rule
        vector<vector<Token>> t  ;
        rule.second->setDerivedStrings(t);

        // Iterate over each group
        for (const auto& group : groups) {
            // If the group contains only one string, add it back to the rule
            if (group.second.size() == 1) {
                rule.second->addDerivedString(group.second[0]);
            }
            else {
                // If the group contains more than one string, create a new non-terminal and add it to the rule
                string newNonTerminal = rule.second->getNonTerminal() + "'";
                Token newtoken , token  ;
                token.setName(newNonTerminal);
                newtoken.setName(group.first);
                vector<Token> vec ;
                vec.push_back(newtoken);
                vec.push_back(token);
                rule.second->addDerivedString(vec);

                // Create a new rule for the new non-terminal
                auto newRule = new CFGRule();
                newRule->setNonTerminal(newNonTerminal);

                // Add the rest of the strings in the group to the new rule
                for (const auto& str : group.second) {
                    vector<Token> newStr(str.begin() + 1, str.end());
                    newRule->addDerivedString(newStr);
                }
                // Add the new rule to the CFG
                cfg[newNonTerminal] = newRule;
            }
        }

    }
}

void LL1_Generator::NonImmediate_LR_Elimination(map<string, CFGRule*>& cfg) {
    vector<string> nonTerminals;

    // Get all non-terminals
    for (const auto& rule : cfg) {
        nonTerminals.push_back(rule.first);
    }

    for (size_t i = 0; i < nonTerminals.size(); ++i) {
        for (size_t j = 0; j < i; ++j) {
            vector<vector<Token>> newDerivedStrings;

            // For each derived string of rule i
            for (const auto& str : cfg[nonTerminals[i]]->getDerivedStrings()) {
                // If the string starts with non-terminal j, replace it with its derived strings
                if (!str.empty() && str[0].getName() == nonTerminals[j]) {
                    for (const auto& replacingStr : cfg[nonTerminals[j]]->getDerivedStrings()) {
                        vector<Token> newStr = replacingStr;
                        newStr.insert(newStr.end(), str.begin() + 1, str.end());
                        newDerivedStrings.push_back(newStr);
                    }
                }
                else {
                    newDerivedStrings.push_back(str);
                }
            }
            // Update the derived strings of rule i
            cfg[nonTerminals[i]]->setDerivedStrings(newDerivedStrings);
        }

        // Eliminate immediate left recursion in rule i
        LR_Elimination(cfg);
    }
}


void LL1_Generator::LR_Elimination(map<string, CFGRule*>& cfg) {
    // Iterate over each rule in the CFG
    for (auto& rule : cfg) {
        vector<vector<Token>> recursive, nonRecursive;

        // Split the derived strings into recursive and non-recursive
        for (const auto& str : rule.second->getDerivedStrings()) {
            if (!str.empty() && str[0].getName() == rule.second->getNonTerminal())
                recursive.push_back(vector<Token>(str.begin() + 1, str.end()));
            else
                nonRecursive.push_back(str);
        }

        // If there are no recursive derived strings, continue to the next rule
        if (recursive.empty())
            continue;

        // Clear the derived strings of the rule
        vector<vector<Token>> t;
        rule.second->setDerivedStrings(t);

        // Create a new non-terminal for the recursive part
        string newNonTerminal = rule.second->getNonTerminal() + "'";

        // Add the non-recursive derived strings to the rule, followed by the new non-terminal
        for (const auto& str : nonRecursive) {
            vector<Token> newStr = str;
            Token newToken;
            newToken.setName(newNonTerminal);
            newStr.push_back(newToken);
            rule.second->addDerivedString(newStr);
        }

        // Create a new rule for the new non-terminal
        auto newRule = new CFGRule();
        newRule->setNonTerminal(newNonTerminal);

        // Add the recursive derived strings to the new rule, followed by the new non-terminal
        for (const auto& str : recursive) {
            vector<Token> newStr = str;
            Token newToken;
            newToken.setName(newNonTerminal);
            newStr.push_back(newToken);
            newRule->addDerivedString(newStr);
        }

        // Add an empty string to the new rule
        Token eps ;
        eps.setName("epsilon");
        eps.setIsTerminal(true);
        vector<Token> emptyStr;
        emptyStr.push_back(eps);
        newRule->addDerivedString(emptyStr);

        // Add the new rule to the CFG
        cfg[newNonTerminal] = newRule;
    }
}


