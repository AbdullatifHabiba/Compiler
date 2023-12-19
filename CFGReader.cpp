// CFG_Reader.cpp
#include "CFGReader.h"
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

const std::vector<CFGRule>& CFG_Reader::getRules() const {
    return rules;
}

const std::string &CFG_Reader::getStartState() const {
    return start;
}
void CFG_Reader::buildRule(const std::string& line) {
    auto *rule = new CFGRule();

    std::vector<std::string> tokens;
    bool eq = false;
    for (int i = 0; i < static_cast<int>(line.size()); ++i) {
        std::string name;

        if (isalpha(line[i])) {
            name += line[i];
            while (i + 1 < static_cast<int>(line.size()) && (isalpha(line[i + 1]) || line[i + 1] == '_' || line[i + 1] == '\''))
                name += line[++i];

            tokens.push_back(name);
           if(eq){ Token t = Token();
            t.setName( name);
            t.setIsTerminal(false);
            rule->addDerivedString(t);}
        } else if (line[i] == '\'') {  // terminal
            std::string x = "'";
            while (line[i + 1] != '\'')
                name += line[++i];

            ++i;
            x += name + "'";

            tokens.push_back(x);
            Token t = Token();
            t.setName( x);
            t.setIsTerminal( true);
            rule->addDerivedString(t);
        } else if (line[i] == '=' || line[i] == '|') {
            eq = true;
            name += line[i];
            tokens.push_back(name);
        } else if (line[i] == '\\') {
            if (line[i + 1] == 'L') {
                tokens.emplace_back("\\L");
                Token t = Token();
                t.setName( "\\L");
                t.setIsTerminal( true);
                rule->addDerivedString(t);
                ++i;
            }
        }
    }

    if (tokens.empty())
        return;

    bool flag = false;
    bool is_split = false;
    std::string non_terminal;
    std::string split;



    for (const auto& token : tokens) {
        cout << token << endl;

        if (token != "|" && token != "=" && is_split) {
            split += ' ';
        }

        if (token == "|" && is_split) {

            split = "";
            is_split = false;
            continue;
        }

        if (!flag) {
            flag = true;
            non_terminal = token;
        } else {
            if (token != "=") {
                is_split = true;
                split += token;
            }
        }
    }

//    if (!split.empty()) {
//        Token t = Token();
//        t.setName( split);
//         if(split[0]=='\'') t.setIsTerminal( true);
//         else t.setIsTerminal(   false);
//        rule->addDerivedString(t);
//    }

    CFG_Reader::ProductionRules.insert(std::pair<std::string, CFGRule*>(non_terminal, rule));
    rule->setNonTerminal(non_terminal);



    if (non_terminal == start) rule->isStart = true;
    if(start.empty()) start = non_terminal;
}

int main() {
    CFG_Reader cfgReader;
    std::string fileName = "/home/abdu/CLionProjects/compilers/cfg_rules.txt";  // Replace with the actual file path

    cfgReader.readRulesFromFile(fileName);

    std::cout << "Start symbol: " << cfgReader.getStartState() << std::endl;

    const std::vector<CFGRule>& rules = cfgReader.getRules();
    std::cout << "Production Rules:\n";
    for(const auto& rule : cfgReader.ProductionRules) {
        std::cout << rule.first << " -> ";
        const std::vector<Token>& derivedStrings = rule.second->getDerivedStrings();
        for (int i = 0; i < static_cast<int>(derivedStrings.size()); ++i) {
            std::cout << derivedStrings[i].getName() ;
            cout << " " << derivedStrings[i].isTerminal<< endl;
            if (i + 1 < static_cast<int>(derivedStrings.size()))
                std::cout << " | ";
        }
        std::cout << std::endl;
    }


    return 0;
}
