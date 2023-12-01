#include <iostream>
#include "Scanner.h"
#include "NFA.h"
#include "Matcher.h"

int main() {
    // intilize  scanner
    Scanner scanner;

    string file_name ="/home/abdu/CLionProjects/compilers/input.txt";
    scanner.scan(file_name);
    NFA* final= scanner.getFinalNFA();
    set<NFA_State*> visited;
    final-> printNFA(final->start_state, visited);

    Matcher matcher;
    matcher.set_output_file_name("output.txt");

    // Test the Matcher with tokens from the file
    matcher.matchFile("/home/abdu/CLionProjects/compilers/test.txt", final->start_state);

    // Print the symbol table
    std::vector<std::string> symbol_table = matcher.get_sym_table();
    std::cout << "Symbol Table:" << std::endl;
    for (const auto &symbol : symbol_table) {
        std::cout << symbol << std::endl;
    }






    return 0;
}
