#include <iostream>
#include "Scanner.h"
#include "NFA.h"

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


}

