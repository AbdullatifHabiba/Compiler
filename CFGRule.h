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


    void setNonTerminal(const std::string& nterminal);
    void addDerivedString(const Token& derivedString);

    [[nodiscard]] const std::string& getNonTerminal() const;
    [[nodiscard]] const std::vector<Token>& getDerivedStrings() const;
    bool isStart{};



private:
    bool isStartRule{};
    std::string nonTerminal;
    std::vector<Token> derivedStrings;


};

#endif // CFG_RULE_H
