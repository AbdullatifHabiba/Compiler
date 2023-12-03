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
    set<NFA_State*> visited;
    final-> printNFA(final->start_state, visited);
//  DFA States Test
  cout << "DFA States Test" << endl;
   DFA D = *new DFA();
    set<DFA_State*> DFA_ = D.convert_NFA_to_DFA(final->start_state);
    cout << "\nSize = " << DFA_.size() <<endl;
    D.printDFA(DFA_);








    return 0;
}
