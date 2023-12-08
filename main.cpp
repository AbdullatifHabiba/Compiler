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
    for (const auto& row : matcher.getIdentifiersList()) {
        std::cout << row << std::endl;
    }
    return 0;



}
