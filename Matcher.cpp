#include <sstream>
#include <iterator>
#include <utility>
#include "Matcher.h"
using namespace std;
Matcher::Matcher() {
    // Constructor implementation
    out = "";
    transitionTable = std::vector<std::string>();
    output_file_name = "";
}

Matcher::~Matcher() = default;

void Matcher::matchFileWithDFA(const std::string& file_name, DFA_State* start) {
    // Read and tokenize the file
    std::string str, line;
    std::ifstream myfile(file_name.c_str());
    if (myfile.is_open()) {
        while (getline(myfile, line)) {
            str.append( ' ' + line);
        }
        myfile.close();
    } else{
        std::cout << "can't open file" << std::endl;
    }
    std::cout << str << std::endl;

    std::istringstream buf(str);
    std::istream_iterator<std::string> beg(buf), end;
    std::vector<std::string> tokens(beg, end);

    // Process each token using the runDFA method
    for (const auto& token : tokens) {
       // cout << "token : " << token << endl;
        cout << "str: " << token << " token : "<<start->get_token() << endl;

        runDFA(token, start);
    }

    // Write the output to the file
    writeOutputToFile(output_file_name);
}

std::vector<std::string> Matcher::getTransitionTable() {
    return transitionTable;
}

void Matcher::setOutputFileName(string outputFile) {
    this->output_file_name = std::move(outputFile);
}

void Matcher::writeOutputToFile(const std::string& name) {
    std::ofstream myfile(name.c_str());
    if (myfile.is_open()) {
        myfile << out;
        myfile.close();
    }
}

bool Matcher::runDFA(std::string str, DFA_State* start) {
    int pos = 0;
    DFA_State *temp = start;
    DFA_State *last = nullptr;

    if (temp->isFinalState()) {
        last = temp;
        pos = 0;
    }

    for (int i = 0; i < str.size(); i++) {
        temp = temp->get_next(str[i]);
        cout<<str[i]<<" "<<temp->get_token()<<" "<<"  state_number "<<  temp->get_id() <<endl;
        if (temp->isFinalState()) {
            last = temp;
            pos = i;
        }
    }

    if (temp->isFinalState() && temp == last) {
        // Token with acceptance, process the accepted part

        // Token is accepted
        std::string type = temp->get_token();
        cout << "type : " << type << endl;

        if (type == "keyword" || type == "punctuation") {
            this->out = this->out + str + '\n';
        } else {
            this->out = this->out + type + '\n';
        }

        if (type == "id") {
            this->transitionTable.push_back(str);
        }

        return true;
    } else {
        if (last != nullptr && last->isFinalState()) {
            // Token with acceptance, process the accepted part
            std::string type = last->get_token();
            cout << "type : " << type << endl;
            if (type == "keyword" || type == "punctuation") {
                this->out = this->out + str.substr(0, pos + 1) + '\n';
            } else {
                this->out = this->out + type + '\n';
            }

            if (type == "id") {
                this->transitionTable.push_back(str.substr(0, pos + 1));
            }

            std::string reminder = str.substr(pos + 1);
            return runDFA(reminder, start);
        } else {
            // Token not accepted
            this->out = this->out + "ERROR in symbol  " + str + '\n';
        }
    }

    return false;
}
