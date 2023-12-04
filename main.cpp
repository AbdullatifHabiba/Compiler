#include <iostream>
#include "Scanner.h"
#include "NFA.h"

#include "DFA.h"
#include "Matcher.h"

int main() {
    // intilize  scanner
    Scanner scanner;

    string file_name ="C:/Users/Hardware/Desktop/TODO/Compiler1/input.txt";
    string test_file_name ="C:/Users/Hardware/Desktop/TODO/Compiler1/test.txt";

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

    cout <<"start matching"<<endl;
    // match the input file with the DFA
    Matcher matcher;
    matcher.matchFileWithDFA(test_file_name, *DFA_.begin());
    cout<< "------------------------------->>>>>>>>>>>>>>>>>>>>>>>>>Start state "<<DFA_.begin().operator*()->get_id()<<endl;
    matcher.writeOutputToFile("output.txt");
    matcher.getTransitionTable();
    // print the transition table
    for (const auto& row : matcher.getTransitionTable()) {
        std::cout << row << std::endl;
    }
    return 0;



}
