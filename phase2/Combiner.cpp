//
// Created by abdu on 12/23/23.
//

#include <stack>
#include "Combiner.h"
#include <fstream>
#include <iostream>
#include "ParsingTable.h"
using namespace std;


void Combiner::setLexicalTerminals(const vector<string> &lexical_terminals1) {
    this->lexical_terminals = lexical_terminals1;

}

void Combiner::setTable(const map<Token, map<Token, pair<string, vector<Token>>>> &input_table) {
    this->table = input_table;

}

void Combiner::LL_Parse(const Token& start) {

    std::ofstream outfile("cfg_output.txt");
    Token token = Token("$");
    this->parse_stack.push(token);
    this->parse_stack.push(start);

    int index = 0;

    while (true) {
        outfile << "Stack: ";
        cout<<"stack : ";
        print_stack(this->parse_stack,outfile);
        outfile << "Input: ";
        cout<<"input : ";
        for (int i = index; i < this->lexical_terminals.size(); i++) {
            outfile << this->lexical_terminals[i] << " ";
            cout<<this->lexical_terminals[i] << " ";
        }
        outfile << std::endl;
        cout<<endl;
        Token X = this->parse_stack.top();
        string a = this->lexical_terminals[index];

        if (X.getName() == a && a == "$") {
            outfile << "Parser halts (successful completion)" << std::endl;
            break;
        }
        else if (X.getName() != a && a == "$" && X.isTerminal) {

                // insert this token should be in input
                outfile<<"Error:missing  "<< X.getName()<<" , inserted"<<endl;
               // dr<<"Error:missing  "<< X.getName()<<" , inserted"<<endl;
                parse_stack.pop();


        }else if (X.getName() == a) {
            // Terminal
            outfile << "Matched: " << a << std::endl;
            this->parse_stack.pop();
            index++;
        } else {
            // Non-terminalt
            Token ab = Token(a);
            ab.setIsTerminal(true);
            cout<< "non_terminal "<<X.getName()<< X.isTerminal<<endl;
            cout<< "terminal "<<ab.getName()<<endl;
             if(X.getName() == "\\L") {
                this->parse_stack.pop();
                outfile << X.getName() << "-> EPS" << std::endl;
               // dr << X.getName() << "-> EPS" << std::endl;
                continue;
            }
            pair<string,vector<Token>> entry = parsingTable.get_entry(X,ab);
            cout<< "entry.first "<<entry.first<<endl;
            if(entry.first.empty()) { // empty cell
                if(X.isTerminal ){
                    // insert this token should be in input
                    outfile<<"Error:missing  "<< X.getName()<<" , inserted"<<endl;
                    //dr<<"Error:missing  "<< X.getName()<<" , inserted"<<endl;
                    parse_stack.pop();
                }
                else{
                    // discard this token
                    outfile<<"Error: Illegal(" +X.getName()+ " ) - discard  "<<a <<endl;
                    //dr<<"Error: Illegal(" +X.getName()+ " ) - discard  "<<a <<endl;
                    index++;
                }
            }  else if (entry.first == "sync") { // adding sync
                // Error
                string s = "Error sync:: " +  X.getName() + " -> Discarded ";
                outfile << s << std::endl;
                //dr << s << std::endl;
                this->parse_stack.pop();
            } else if (entry.first == "error") {
                // Error
                if(X.isTerminal){
                    // insert this token should be in input
                    outfile<<"Error:missing  "<< X.getName()<<" , inserted"<<endl;
                   // dr<<"Error:missing  "<< X.getName()<<" , inserted"<<endl;
                    parse_stack.pop();
                }
                else{
                    // discard this token
                    outfile<<"Error: Illegal(" +X.getName()+ " ) - discard  "<<a <<endl;
                    //dr<<"Error: Illegal(" +X.getName()+ " ) - discard  "<<a <<endl;
                    index++;
                }

            }
            else {
                this->parse_stack.pop();
                outfile << X.getName() << "-> " ;
                // output the rule
                for (int i = entry.second.size() - 1; i >= 0; i--) {
                    this->parse_stack.push(entry.second[i]);
                    outfile << entry.second[entry.second.size() - 1-i].getName() << " ";
                }
                outfile << std::endl;
              //  dr << std::endl;

            }
        }
    }
    outfile.close();
    //dr.close();




}
std::ofstream dr("derivation.txt");
string derivedTerminals = "";

void Combiner::print_stack(stack<Token> s,std::ofstream& output_file) {
    dr<<derivedTerminals;
    int counter=0;
    while(!s.empty()){
        output_file<<s.top().getName()<<" ";
        cout<<s.top().getName()<<" ";
        bool flag=false,flag2=false;
        if(counter==0){
            flag=true;
        }
        if (s.top().getName() !="$"){
            if(s.top().isTerminal&&(flag || flag2)){
                derivedTerminals.append(s.top().getName()+" ");
                flag2=true;
            }else{
                flag2=false;
            }

            dr<<s.top().getName()<<" ";
        }
        s.pop();
        counter++;
    }
    cout<<endl;
    output_file<<endl;
    dr<<endl;
}

void Combiner::setParsingTable(const ParsingTable &parsingTable1) {
    Combiner::parsingTable = parsingTable1;
}

Combiner::Combiner() = default;


//int min() {
//    Combiner combiner;
//
//    // Initialize lexical terminals ceadb$
//    vector<string> lexical_terminals = {"a", "a", "b", "$"};
//   // vector<string> lexical_terminals = {"c", "e", "a","d","b", "$"};
//
//    combiner.setLexicalTerminals(lexical_terminals);
//
//    // Initialize table
//    map<Token, map<Token, pair<string, vector<Token>>>> table;
//
//    // Add your own table entries
//    // For example, for the rule S -> AbS
//    Token a("a");
//      a.setIsTerminal(true);
//    Token b("b");
//    b.setIsTerminal(true);
//    Token c("c");
//    c.setIsTerminal(true);
//    Token d("d");
//    d.setIsTerminal(true);
//    Token e("e");
//    e.setIsTerminal(true);
//    Token dl("$");
//    dl.setIsTerminal(true);
//    Token S("S");
//    Token A("A");
//
//
//    Token epsilon("EPS");
//    epsilon.setIsTerminal(true);
//    vector<Token> production1 = {A, b, S};
//    vector<Token> production3 = {c, A, d};
//    table[S][a] = make_pair("S->AbS", production1);
//    table[S][b] = make_pair("error", vector<Token>{});
//    table[S][c] = make_pair("S->AbS", production1);
//    table[S][d] = make_pair("error", vector<Token>{});
//    table[S][e] = make_pair("S->e", vector<Token>{e});
//    table[S][dl] = make_pair("EPS", vector<Token>{epsilon});
//
//    table[A][a] = make_pair("A->a", vector<Token>{a});
//    table[A][b] = make_pair("sync", vector<Token>{});
//    table[A][c] = make_pair("A->cAd", production3);
//    table[A][d] = make_pair("sync", vector<Token>{});
//    table[A][e] = make_pair("error", vector<Token>{});
//    table[A][dl] = make_pair("error", vector<Token>{});
//    // Print the table
//    for (const auto &i: table) {
//
//        for (const auto &j: i.second) {
//            cout << "[" << i.first.getName() << " , ";
//            cout << j.first.getName() << " ] ->  ";
//            cout << j.second.first;
//            cout << endl;
//        }
//    }
//        cout << endl;
//        // Add other rules similarly
//
//        combiner.setTable(table);
//
//
//        // Call LL_Parse method
//        combiner.LL_Parse(S);
//
//        return 0;
//    }
//

