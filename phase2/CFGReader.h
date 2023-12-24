//
// Created by abdu on 12/19/23.
//

#ifndef COMPILERS_CFGREADER_H
#define COMPILERS_CFGREADER_H



#include "CFGRule.h"
#include <vector>
#include <map>
#include "Token.h"
using namespace std;
class CFG_Reader {
public:
    CFG_Reader();
    ~CFG_Reader();

    void readRulesFromFile(const std::string& fileName);
    [[nodiscard]] const std::vector<CFGRule>& getRules() const;
    [[nodiscard]] const std::string& getStartState() const;

    void buildRule(const std::string& line);
    map  <std::string, CFGRule*> ProductionRules;

    void print(map<string, CFGRule *> map);

private:
    std::vector<CFGRule> rules;
    string start;

};



#endif //COMPILERS_CFGREADER_H
