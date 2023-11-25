#include <iostream>
#include "Scanner.h"
#include "NFA.h"

int main() {
    // intilize  scanner
    Scanner scanner;

    string file_name ="/home/abdu/CLionProjects/compilers/input.txt";
   NFA* nfa= scanner.scan(file_name);
   for(auto& state : nfa->states)
    {
         cout << state << endl;
         for(auto& transition : state->getTransitions())
         {
              cout << "\t" << transition.first << ": ";
              for(auto& next_state : transition.second)
              {
                cout << next_state << " ";
              }
              cout << endl;
         }
}
}

