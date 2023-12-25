// CFG_Reader.cpp
#include "CFGReader.h"
#include "LL1_Generator.h"
#include <fstream>
#include <iostream>
#include <string>
#include <algorithm>
#include <map>
using namespace std;
CFG_Reader::CFG_Reader() = default;

CFG_Reader::~CFG_Reader() = default;

void CFG_Reader::readRulesFromFile(const std::string& fileName) {
    std::ifstream cfgFile(fileName);

    string input, s;
    bool flag = false;
    while(getline(cfgFile, s))
    {
        for(char i : s)
        {
            if(i == '#' && flag)
            {
                buildRule(input);
                input.clear();
            }
            input += i;
            flag = true;

        }
    }
    buildRule(input);
}

const std::vector<string>& CFG_Reader::get_nonterminals() const {
    return nonterminals;
}

const std::string &CFG_Reader::getStartState() const {
    return start;
}
void CFG_Reader::buildRule(const std::string& line) {
    auto *rule = new CFGRule();
    cout << "line : " << line << endl;
    // set non terminal after # and before =
    vector < string > tokens;

    for(int i = 0; i < (int)line.size(); ++i)
    {
        string name;
        if(isalpha(line[i]))
        {
            name += line[i];
            while(i + 1 < (int)line.size() and (isalpha(line[i + 1]) or line[i + 1] == '_') or line[i+1] == '\'' )
                name += line[++i];

            tokens.push_back(name);
        }
        else if(line[i] == '\'')                   // terminal
        {
            string x = "'";
            while(line[i + 1] != '\'')
                name += line[++i];

            ++i;
            x += name + "'";
            tokens.push_back(x);
        }
        else if(line[i] == '=' or line[i] == '|')
        {
            name += line[i];
            tokens.push_back(name);
        }
        else if(line[i] == '\\')
        {
            if(line[i + 1] == 'L')
            {
                tokens.emplace_back("\\L");
                ++i;
            }
        }
    }
    if(tokens.empty())      return;
    //
    rule->setNonTerminal(tokens[0]);
    vector < Token > tks = vector<Token>();
    for(int i = 2; i < (int)tokens.size(); ++i)
    {
        if(tokens[i] == "|")
        {
            rule->addDerivedString(tks);
            tks = vector<Token>();
        }else{
            Token t = Token();
            t.setName(tokens[i]);
            if(tokens[i][0] == '\'') t.setIsTerminal(true);
            else t.setIsTerminal(false);
            tks.push_back(t);
        }
    }
    rule->addDerivedString(tks);
    ProductionRules.insert(std::pair<std::string, CFGRule*>(tokens[0], rule));
    nonterminals.push_back(tokens[0]);
    if(start.empty())
    {start = tokens[0];
     rule->isStart = true;
    }


}

void CFG_Reader::print(map<string, CFGRule*> map){
    cout << "Production Rules size : " << map.size() << endl;
    std::cout << "Production Rules:::::::::::::::::::::::::::\n";
    for(const auto& rule : map) {
        std::cout << rule.first << " -> ";
        const std::vector<vector<Token>>& derivedStrings = rule.second->getDerivedStrings();
        for(const auto& derivedString : derivedStrings) {
            for(const auto& token : derivedString) {
                std::cout << token.getName() << " ";
                cout << token.isTerminal << " ";
            }
            // cout only if there are more derived strings and the current one is not the last
            if(derivedStrings.size() > 1 && &derivedString != &derivedStrings.back()) std::cout << "| ";

        }
        std::cout << std::endl;
    }
}

int main() {

    CFG_Reader cfgReader;
    std::string fileName = R"(C:\Users\Hardware\Desktop\TODO\Compiler1\phase2\cfg_rules.txt)";  // Replace with the actual file path

    cfgReader.readRulesFromFile(fileName);
    std::cout << "Start symbol: " << cfgReader.getStartState() << std::endl;
    cout << "Production Rules size : " << cfgReader.ProductionRules.size() << endl;
    std::cout << "Production Rules:\n";
    for(const auto& rule : cfgReader.ProductionRules) {
        std::cout << rule.first << " -> ";
        const std::vector<vector<Token>>& derivedStrings = rule.second->getDerivedStrings();
        for(const auto& derivedString : derivedStrings) {
            for(const auto& token : derivedString) {
                std::cout << token.getName() << " ";
                cout << token.isTerminal << " ";
            }
            // cout only if there are more derived strings and the current one is not the last
                     if(derivedStrings.size() > 1 && &derivedString != &derivedStrings.back()) std::cout << "| ";

                    }
        std::cout << std::endl;
    }

    // Apply left factoring and left recursion
    LL1_Generator gen;
    gen.LF_Elimination(cfgReader.ProductionRules);
    cout<<"\n\n\n\n";
    cout<< "LF Elimination" << endl;
    cfgReader.print(cfgReader.ProductionRules);
    gen.NonImmediate_LR_Elimination(cfgReader.ProductionRules, cfgReader.get_nonterminals());
    cout<<"\n\n\n\n";
    cout<< "LR Elimination" << endl;
    cfgReader.print(cfgReader.ProductionRules);
    return 0;
}
