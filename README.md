# Lexical Analyzer Generator

## Objective
This phase of the assignment aims to practice techniques for building automatic lexical analyzer generator tools.

## Description
Your task in this phase of the assignment is to design and implement a lexical analyzer generator tool.

1. **Functionality**:
   - The lexical analyzer generator is required to automatically construct a lexical analyzer from a regular expression description of a set of tokens.
   - The tool constructs a nondeterministic finite automata (NFA) for the given regular expressions.
   - It combines these NFAs together with a new starting state.
   - Converts the resulting NFA to a DFA, minimizes it, and emits the transition table for the reduced DFA.
   - It generates a lexical analyzer program that simulates the resulting DFA machine.

2. **Lexical Analysis**:
   - The generated lexical analyzer reads its input one character at a time until it finds the longest prefix of the input, which matches one of the given regular expressions.
   - It creates a symbol table and inserts each identifier in the table.
   - If more than one regular expression matches some longest prefix of the input, the lexical analyzer breaks the tie in favor of the regular expression listed first in the regular specifications.
   - If a match exists, the lexical analyzer produces the token class and the attribute value.
   - If none of the regular expressions matches any input prefix, an error recovery routine is called to print an error message and to continue looking for tokens.

3. **Testing**:
   - The lexical analyzer generator is required to be tested using the given lexical rules of tokens of a small subset of Java.
   - Use the provided simple program to test the generated lexical analyzer.

4. **Integration with Parser**:
   - The generated lexical analyzer will integrate with a generated parser which you should implement in phase 2 of the assignment.
   - The lexical analyzer is to be called by the parser to find the next token.

## How to Use
- **Input**: Provide a regular expression description of a set of tokens.
- **Output**: The tool generates a lexical analyzer program along with a transition table for the reduced DFA.

