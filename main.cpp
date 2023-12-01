#include <iostream>
#include "Scanner.h"
#include "NFA.h"
#include "DFA.h"

int main() {
    // intilize  scanner
    Scanner scanner;

    string file_name ="C:/Users/Hardware/Desktop/TODO/Compiler1/input.txt";
    scanner.scan(file_name);
    NFA* final= scanner.getFinalNFA();
//    final->printNFA();
//
//    for(const auto &identifier : scanner.identifiers) {
//        cout << identifier.first << " : " << identifier.second << endl;
//    }
    set<NFA_State*> visited;
    final-> printNFA(final->start_state, visited);
//  DFA States Test
   /* DFA D = *new DFA();
    set<DFA_State*> DFA_ = D.convert_NFA_to_DFA(final->start_state);
    cout << "\nSize = " << DFA_.size() <<endl;
    D.printDFA(DFA_);*/



}

