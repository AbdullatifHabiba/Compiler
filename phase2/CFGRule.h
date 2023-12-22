// CFGRule.h
#ifndef CFG_RULE_H
#define CFG_RULE_H

#include <string>
#include <vector>
#include <map>
#include "Token.h"

using namespace std;
class CFGRule {
public:
    CFGRule();
    ~CFGRule();


    void setNonTerminal(const std::string& non_terminal);
    void addDerivedString(const vector<Token>& derivedString);

    [[nodiscard]] const std::string& getNonTerminal() const;
    [[nodiscard]] const std::vector<vector<Token>>& getDerivedStrings() const;
    bool isStart{};



private:
    std::string nonTerminal;
    std::vector<vector<Token>> derivedStrings;


};

#endif // CFG_RULE_H
