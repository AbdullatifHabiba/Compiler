#include <iostream>
#include "Scanner.h"
#include "NFA.h"

#include "DFA.h"
#include "Minimize.h"
#include "Matcher.h"
int main() {
    // intilize  scanner
    Scanner scanner;

    string file_name ="/home/abdu/CLionProjects/compilers/input.txt";
    string test_file_name ="/home/abdu/CLionProjects/compilers/test.txt";

    scanner.scan(file_name);
    NFA* final= scanner.getFinalNFA();

//    final->printNFA();

   for(const auto &identifier : scanner.identifiers) {
       cout << identifier.first << " : " << identifier.second << endl;
    }
    set<NFA_State*> visited;
//    final-> printNFA(final->start_state, visited);

//  DFA States Test

    DFA D = *new DFA();
    set<DFA_State*> DFA_ = D.Converter(final->start_state);
    cout << "\nDFA # States = " << DFA_.size() <<endl<<endl;
    Minimize MD = *new Minimize();
//    set<DFA_State*> MDFA_ = MD.DFA_min(DFA_);
//    cout<<"the size :::   ---->" <<MDFA_.size()<<endl;
//    //D.printDFA(DFA_);
////    D.printDFA(MDFA_);
    cout <<"start matching"<<endl;
    // match the input file with the DFA
    Matcher matcher;
    matcher.matchFileWithDFA(test_file_name, *DFA_.begin());
    cout<< "------------------------------->>>>>>>>>>>>>>>>>>>>>>>>>Start state "<<DFA_.begin().operator*()->get_id()<<endl;
    matcher.writeOutputToFile("output.txt");
    // print the transition table
    for (const auto& row : matcher.getTransitionTable()) {
        std::cout << row << std::endl;
    }
    return 0;



}
