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

    DFA *D = new DFA();
    set<DFA_State*> DFA_ = D->Converter(final->start_state);
    cout << "\nDFA # States = " << DFA_.size() <<endl<<endl;
//    D->printTransitionTable(DFA_);
    auto *MD = new Minimize();
    set<DFA_State*> MDFA_ = MD->DFA_min(DFA_);
    cout<<"the MDFA_ size :::   ---->" <<MDFA_.size()<<endl;
    MD->printTransitionTable(MDFA_);
    cout <<"start matching"<<endl;
    cout<< "------------------------------->>>>>>>>>>>>>>>>>>>>>>>>>Start state "<<MD->get_start_state()->get_id()<<endl;
    Matcher matcher;
    matcher.matchFileWithDFA(test_file_name, MD->get_start_state());
    matcher.writeOutputToFile("output.txt");
    // print the transition table
    for (const auto& row : matcher.getTransitionTable()) {
        std::cout << row << std::endl;
    }
    return 0;



}
