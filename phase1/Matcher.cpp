#include <sstream>
#include <iterator>
#include <utility>
#include "Matcher.h"
using namespace std;
Matcher::Matcher() {
    // Constructor implementation
    out = "";
    IdentifiersList = std::vector<std::string>();
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

std::vector<std::string> Matcher::getIdentifiersList() {
    return IdentifiersList;
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
        cout<<str[i]<<" "<<temp->get_token()<<" "<<"  state_number "<<  temp->get_id()<<"  " << temp->isFinalState()<<endl;
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
            terminals.emplace_back(str);

        } else {
            this->out = this->out + type + '\n';
            if(type =="assign"){
                terminals.emplace_back("=");
            } else terminals.emplace_back(type);

        }


        if (type == "id") {
            this->IdentifiersList.push_back(str);
        }

        return true;
    } else {
        if (last != nullptr && last->isFinalState()) {
            // Token with acceptance, process the accepted part
            std::string type = last->get_token();
            cout << "type : " << type << endl;
            if (type == "keyword" || type == "punctuation") {
                this->out = this->out + str.substr(0, pos + 1) + '\n';
                terminals.push_back(str.substr(0, pos + 1));

            } else {
                this->out = this->out + type + '\n';
                if(type =="assign"){
                    terminals.emplace_back("=");
                } else terminals.emplace_back(type);

            }

            if (type == "id") {
                this->IdentifiersList.push_back(str.substr(0, pos + 1));
            }

            std::string reminder = str.substr(pos + 1);
            return runDFA(reminder, start);
        } else {
            // Token not accepted
            cout << "str  " << str << endl;
            // if size of str is 1
            if (str.size() == 1) {
                this->out = this->out + "not accepted symbol  " + str + '\n';
               // terminals.push_back(str);
                return false;
            }
            std::string reminder = str.substr(pos + 1);
            this->out = this->out + "not accepted symbol  " + str[pos] + '\n';
            //terminals.push_back(str.substr(pos, pos + 1));

            return runDFA(reminder, start);
        }
    }

    return false;
}

const vector<string> &Matcher::getTerminals() const {
    return terminals;
}
