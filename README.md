# Objective
This phase of the assignment aims to practice techniques for building automatic lexical
analyzer generator tools.
## Description
Your task in this phase of the assignment is to design and implement a lexical analyzer
generator tool.

1- `The lexical analyzer generator is required to automatically construct a lexical
analyzer from a regular expression description of a set of tokens. The tool is required
to construct a nondeterministic finite automata (NFA) for the given regular
expressions, combine these NFAs together with a new starting state, convert the
resulting NFA to a DFA, minimize it and emit the transition table for the reduced DFA
together with a lexical analyzer program that simulates the resulting DFA machine.
`

2- `The generated lexical analyzer has to read its input one character at a time, until it
finds the longest prefix of the input, which matches one of the given regular
expressions. It should create a symbol table and insert each identifier in the table. If
more than one regular expression matches some longest prefix of the input, the lexical
analyzer should break the tie in favor of the regular expression listed first in the
regular specifications. If a match exists, the lexical analyzer should produce the token
class and the attribute value. If none of the regular expressions matches any input
prefix, an error recovery routine is to be called to print an error message and to
continue looking for tokens.`

3- T`he lexical analyzer generator is required to be tested using the given lexical rules of
tokens of a small subset of Java. Use the given simple program to test the generated
lexical analyzer.`

4- `Keep in mind that the generated lexical analyzer will integrate with a generated
parser which you should implement in phase 2 of the assignment such that the lexical
analyzer is to be called by the parser to find the next token.`