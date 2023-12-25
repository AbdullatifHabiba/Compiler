

// Created by u s e r on 21/12/2023.
//

#include "ParsingTable.h"
#include "CFGRule.h"
#include "Token.h"
#include "CFGReader.h"

using namespace std;
//std::vector<CFGRule>& rules
ParsingTable::ParsingTable(const  std::map<std::string, CFGRule*> &rules,const string startState) {
    //get all non-terminals in a list
    for(auto r : rules){
        for(auto prods : r.second->getDerivedStrings()){
            for(auto prod:prods){
                if(prod.isTerminal){
                    this->TerminalsList.insert(prod);
                }
            }
        }

        Token symbol = Token(r.first);
        symbol.setIsTerminal(false);
        nonTerminalsList.push_back(symbol);
        this->grammar.insert({symbol, *r.second});
    }

    for(auto gr:this->grammar){
        cout<< gr.first.getName()<<endl;
        for(auto hhabd : gr.second.getDerivedStrings()){

            for (auto i : hhabd) {
            cout<< i.getName()<<", ";
            }
        }
    cout<<endl;
    }

    //Return to check the assumption
    string start_symbol = startState;
    Token end_symbol = Token("$");
    end_symbol.setIsTerminal(true);

    for(auto r : rules){
        Token rToken = Token(r.first);
        rToken.setIsTerminal(false);
        First_computation(rToken,* r.second);
        this->follow.insert({r.first, {}});
    }


    for(const auto& F:this->first){
        cout<<F.first<< "--> ";
        for(const auto& item : F.second){
            cout<<item.getName()<<", ";
        }
        cout<<endl;
    }
//------------------------------------------
    this->follow.at(start_symbol).insert(end_symbol); // rule 1
    this->Terminals_follow_nonTerminals();
    cout<<"After Terminals_follow_nonTerminals"<<endl;
    this->Right_most_follow();
    cout<<"After Right_most_follow"<<endl;

    cout<<"Follow coming beatch"<< "--> "<<endl;

    for(const auto& F:this->follow){
        cout<<F.first<< "--> ";
        for(const auto& item : F.second){
            cout<<item.getName()<<", ";
        }
        cout<<endl;
    }

    Create_table();
    cout<<"After Create_table "<<endl;
}

//Function to get first for token 'symbol'
set<Token> ParsingTable::get_first(Token &symbol) {
    if(!symbol.isTerminal){
        return this->first.at(symbol.getName());
    }
    set<Token> first_set = {symbol};
    return first_set;
}

set<Token> ParsingTable::get_follow(Token &symbol) {
    return this->follow.at(symbol.getName());
}

//Function to get production which used to get supplied first for the parsing table
vector<Token> ParsingTable::Production_of_first(Token &non_terminal, Token &first) {

    bool found = false;
    vector<Token> ret ;
    CFGRule prods = this->grammar.at(non_terminal);

    for(auto prod : prods.getDerivedStrings()){
        set<Token> curr_first = {eps_symbol};
        for(auto symbol : prod){
            const set<Token> first_set = this->get_first(symbol);
            curr_first.insert(first_set.begin(), first_set.end());
            if(first_set.find(eps_symbol) == first_set.end() ){
                curr_first.erase(eps_symbol);
                break;}
        }
        if(curr_first.find(first) != curr_first.end()){
            ret = prod;
            if(!found){
                found = true ;
            }
            else{
                cout << "Error because " << first.getName() << " " << first.isTerminal << "\n";
                throw logic_error("2 production can't drive the same first symbol (Not LL1)");
            }
        }
    }
    return  ret;
}

void ParsingTable::Terminals_follow_nonTerminals(){

    for(auto it : this->grammar ){
        for(auto prod : it.second.getDerivedStrings()){
            set<Token> curr_follow;
            for(int i = prod.size() - 1 ; i >= 0 ; i-- ){
                if(!prod[i].isTerminal){
                    this->follow.at(prod[i].getName()).insert(curr_follow.begin(), curr_follow.end());
                    // update curr_first
                    set<Token> first_set = this->first.at(prod[i].getName());
                    // if no epsilon then clear the follow as the follow of behind non-terminal
                    // at most will be the first of this non-terminal
                    if(first_set.find(eps_symbol) == first_set.end()){
                        // reset
                        curr_follow.clear();
                    }
                        // if there is epsilon then the follow of last can be also follow of
                        // the non-terminal behind it, so we don't clear the first
                    else{
                        first_set.erase(eps_symbol);
                    }
                    curr_follow.insert(first_set.begin(), first_set.end());
                }
                    //if terminal clear and add this terminal to be the follow of the Non-terminal behind it
                else if( prod[i].isTerminal) {
                    curr_follow.clear();
                    curr_follow.insert(prod[i]);
                }
            }
        }
    }
}

void ParsingTable::Right_most_follow(){
    while (true){ // keep apply the rule until there is no change in the non-terminals follow sets
        bool change = false;
        int old_size, new_size;
        for(auto  it : this->grammar){
            const set<Token> curr_follow = this->follow.at(it.first.getName());//follow of LHS
            for(auto prod : it.second.getDerivedStrings()){
                for(int i = prod.size() - 1 ; i >= 0 && !prod[i].isTerminal ; i-- ) {
                    set<Token> &follow_set = this->follow.at(prod[i].getName());//follow of right most NT
                    old_size = follow_set.size();
                    follow_set.insert(curr_follow.begin(), curr_follow.end());
                    new_size = follow_set.size();
                    change = change || (old_size != new_size);
                    set<Token> first_set = this->first.at(prod[i].getName());
                    //if no epsilon
                    if(first_set.find(eps_symbol) == first_set.end()){
                        break;
                    }
                }

            }
        }
        if (!change) break;
    }
}

//Done
void ParsingTable::First_computation(const Token &non_terminal, const CFGRule &prods) {
    cout<<non_terminal.getName()<<"   This is nonterminal"<<endl;
    if(this->first.find(non_terminal.getName()) != this->first.end()){
        return; // already computed
    }
    this->first.insert({non_terminal.getName(), {} });
    this->first.at(non_terminal.getName()).insert(eps_symbol);
    set<Token> &curr_first = this->first.at(non_terminal.getName()) ;
    cout<<first.at(non_terminal.getName()).size()<<"   size of curr_first"<<endl;
    bool has_eps = false; // control possibility of adding eps to the first set
    for(const auto& prod : prods.getDerivedStrings()){
        bool curr_eps = true; // check if eps should be added to the first set of this production

        for(const auto& symbol : prod){
            if(symbol.getName()==eps_symbol.getName()){
                // do nothing
            }
            else if (symbol.isTerminal){
                curr_first.insert(symbol);
                curr_eps = false;
            }
            else if (!symbol.isTerminal){
                First_computation(symbol, this->grammar.at(symbol));
                set<Token> first_set = this->first.at(symbol.getName());
                curr_first.insert(first_set.begin(), first_set.end());
                if(first_set.find(eps_symbol) == first_set.end()){
                    curr_eps = false;
                }
            }
            if(!curr_eps) break;
        }
        has_eps =  has_eps || curr_eps;
    }
    //none of the productions has EPS
    if(!has_eps){
        curr_first.erase(eps_symbol);
    }
}

//unordered_map<ParserToken nonterminal, unordered_map<ParserToken terminal, pair<string type, vector<ParserToken> production>>>
void ParsingTable::Create_table(){
    vector<Token> epsProd = {eps_symbol};
    //loop on all non-terminals
    for(auto nonTerm: this->nonTerminalsList) {
        set<Token> firstSet = get_first(nonTerm);
        set<Token> followSet = get_follow(nonTerm);
        // This should be at file scope
        map <Token,pair<string,vector<Token>>> tableRow;
        bool hasEpsilon = false;

        for (auto itr : firstSet) {
            if (itr.getName()==eps_symbol.getName()) {
                //No production for epsilon in first
                //it will be handled in follow
                hasEpsilon = true;
                continue;
            }
            //get production of first for current non-terminal and put in its entry
            tableRow.insert({ itr, make_pair("production", Production_of_first(nonTerm, itr))});
        }

        for (auto itr : followSet) {
            if (hasEpsilon) {
                tableRow.insert({ itr, make_pair("production", epsProd)});
            }
            else {
                tableRow.insert({itr, {"sync", {}}});
            }
        }
        this->Table.insert({nonTerm, tableRow});
    }
}

pair<string, vector<Token>> ParsingTable::get_entry(Token& non_terminal, Token& terminal) {
    map<Token, pair<string, vector<Token>>> row = this->Table.at(non_terminal);
    if (row.find(terminal) == row.end()) { //empty entry
        return {"error",{}};
    }
    return row.at(terminal);
}

void ParsingTable::Print_table(string path) {
    ofstream myFile;
    vector<string> terminalsVector;

    for (auto itr : this->TerminalsList) {
        if(itr.getName()==eps_symbol.getName()){ continue;}
        terminalsVector.push_back(itr.getName());
    }
    terminalsVector.push_back("$");

    myFile.open(path);
//    myFile << "non-terminal/terminal";
    bool first=true;
    for (auto itr : terminalsVector) {
        if(first){
            myFile << "  "<<(itr);
            first=false;
        }
        else{
        myFile << ", " << (itr);
        }
    }
    myFile << "\n";

    for (auto itr : this->Table) {
        myFile << itr.first.getName() << ", " ;//NT
        for (auto term :terminalsVector) {
            Token temp1 = itr.first;
            Token temp2 = Token(term);
            temp2.setIsTerminal(true);
            auto entry = get_entry(temp1, temp2);
            if (entry.first == "error") {
                myFile << "ER, ";
            }
            else if(entry.first == "sync") {
                myFile << entry.first << ", ";
            }
            else {
                myFile << get_production_name(entry.second) << ", ";
            }
        }
        myFile << "\n";
    }

    myFile.close();
}

string ParsingTable::get_production_name(vector<Token> vec) {
    string str1 = "";
    string str2 ;
    for (auto itr : vec) {
        str2 = itr.getName();
        str1.append( str2  + " ");
    }
    return str1;
}

ParsingTable::ParsingTable() {

}

int mai() {
    CFG_Reader cfgReader;
    std::string fileName = "D:\\studying\\Compilers\\ass1\\C\\Compiler\\phase2\\test.txt";  // Replace with the actual file path

    cfgReader.readRulesFromFile(fileName);

    ParsingTable PT = ParsingTable( cfgReader.ProductionRules, cfgReader.getStartState() );

    PT.Print_table("D:\\studying\\Compilers\\ass1\\C\\Compiler\\phase2\\OUT.txt");

    return 0;
}