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

map<string, CFGRule> LL1_Generator::LR_Elimination(map<string, CFGRule *>& LR_map) {
    return {};
}

