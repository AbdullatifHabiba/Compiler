#include <iostream>
#include "phase1/Scanner.h"
#include "phase1/NFA.h"

#include "phase1/DFA.h"
#include "phase1/Minimize.h"
#include "phase1/Matcher.h"
#include "phase2/LL1_Generator.h"
#include "phase2/ParsingTable.h"
#include "phase2/Combiner.h"
#include "phase2/CFGReader.h"

int main() {
    // intilize  scanner
    Scanner scanner;

    string file_name ="/home/abdu/CLionProjects/compilers/input.txt";
    string test_file_name ="/home/abdu/CLionProjects/compilers/test.txt";

    scanner.scan(file_name);
    NFA* final= scanner.getFinalNFA();

//    final->printNFA();

   for(const auto &identifier : scanner.definitions) {
       cout << identifier.first << " : " << identifier.second << endl;
    }
    set<NFA_State*> visited;
//    final-> printNFA(final->start_state, visited);

//  DFA States Test

    DFA *D = new DFA();
    set<DFA_State*> DFA_ = D->Converter(final->start_state);
    cout << "\nDFA # States = " << DFA_.size() <<endl<<endl;
//    D->printMinGraph(DFA_);
    auto *MD = new Minimize();
    set<DFA_State*> MDFA_ = MD->minimize_dfa_states(DFA_);
    cout<<"MinDfa   # States =  " <<MDFA_.size()<<endl;
    MD->printMinGraph(MDFA_);
    // print the table of the min DFA
    D->printTransitionTable(MDFA_);
    cout <<"start matching"<<endl;
    cout<< "-->>Start state "<<MD->get_start_state()->get_id()<<endl;
    Matcher matcher;
    matcher.setOutputFileName("output.txt");
    matcher.matchFileWithDFA(test_file_name, MD->get_start_state());
    // print the IdentifiersList
      vector<string> trs=  matcher.getTerminals();
      cout<<"terminals"<<endl;
        for (const auto & tr : trs) {
            cout<<tr<<endl;
        }
    CFG_Reader cfgReader;
    std::string fileName = "/home/abdu/CLionProjects/compilers/phase2/cfg_rules.txt";  // Replace with the actual file path

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
    ParsingTable PT = ParsingTable( cfgReader.ProductionRules, cfgReader.getStartState() );
    PT.Print_table("parse_table_OUT.txt");
    Combiner combiner;
    combiner.setParsingTable(PT);
    trs.emplace_back("$");
    combiner.setLexicalTerminals(trs);

    combiner.LL_Parse(Token(cfgReader.getStartState()));


    return 0;



}
