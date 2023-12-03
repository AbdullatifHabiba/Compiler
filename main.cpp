#include <iostream>
#include "Scanner.h"
#include "NFA.h"

#include "DFA.h"

int main() {
    // intilize  scanner
    Scanner scanner;

    string file_name ="/home/abdu/CLionProjects/compilers/input.txt";

    scanner.scan(file_name);
    NFA* final= scanner.getFinalNFA();

    final->printNFA();

   for(const auto &identifier : scanner.identifiers) {
       cout << identifier.first << " : " << identifier.second << endl;
    }
    set<NFA_State*> visited;
    final-> printNFA(final->start_state, visited);

//  DFA States Test

    DFA D = *new DFA();
    set<DFA_State*> DFA_ = D.Converter(final->start_state);
    cout << "\nDFA # States = " << DFA_.size() <<endl<<endl;
    //Print the whole DFA transactions
    //D.printDFA(DFA_);

    //Print the DFA Information like each final state token
    // and NFA States inside each DFA State
    D.printDFA_data(DFA_);
}
