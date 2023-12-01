#include <sstream>
#include <iterator>
#include "Matcher.h"
using namespace std;
Matcher::Matcher() {
    // Constructor implementation
}

Matcher::~Matcher() {
    // Destructor implementation
}

void Matcher::matchFile(const string& file_name, NFA_State* start) {
    // Read and tokenize the file
    string str = "", line;
    ifstream myfile(file_name.c_str());
    if (myfile.is_open()) {
        while (getline(myfile, line)) {
            str = str + ' ' + line;
        }
        myfile.close();
    } else{
        cout<<"can't open file"<<endl;
    }
    cout<<str<<endl;

    std::istringstream buf(str);
    std::istream_iterator<std::string> beg(buf), end;
    std::vector<std::string> tokens(beg, end);

    // Process each token using the run method
    for (const auto& token : tokens) {
        run(token, start);
    }

    // Write the output to the file
    write_output_file(output_file_name);
}

std::vector<std::string> Matcher::get_sym_table() {
    return symbol_table;
}

void Matcher::set_output_file_name(std::string output_file_name) {
    this->output_file_name = output_file_name;
}

void Matcher::write_output_file(std::string name) {
    std::ofstream myfile(name.c_str());
    if (myfile.is_open()) {
        myfile << out;
        myfile.close();
    }
}

bool Matcher::run(std::string str, NFA_State* start) {
    int pos = 0, error = -1;
    NFA_State *temp = start;
    NFA_State *last = nullptr;

    if (temp->isFinalState()) {
        last = temp;
        pos = 0;
    }

    for (int i = 0; i < str.size(); i++) {
        if (str[i] == '!') {
            if (i + 1 < str.size()) {
                if (str[i + 1] != '=') {
                    error = i;
                    break;
                }
            }
        }

        temp = temp->getTransitions()[str[i]][0]; // Assuming non-deterministic transitions, adjust accordingly

        if (temp->get_id() == -1) {
            error = i;
            break;
        } else if (temp->isFinalState()) {
            last = temp;
            pos = i;
        }
    }

    if (temp->isFinalState() && temp == last) {
        // Token is accepted
        std::string type = temp->get_token();

        if (type == "Keyword" || type == "Punctuation") {
            this->out = this->out + str + '\n';
        } else {
            this->out = this->out + type + '\n';
        }

        if (type == "id") {
            this->symbol_table.push_back(str);
        }

        return true;
    } else {
        if (last != nullptr && last->isFinalState()) {
            // Token with acceptance, process the accepted part
            std::string type = last->get_token();
            if (type == "Keyword" || type == "Punctuation") {
                this->out = this->out + str.substr(0, pos + 1) + '\n';
            } else {
                this->out = this->out + type + '\n';
            }

            if (type == "id") {
                this->symbol_table.push_back(str.substr(0, pos + 1));
            }

            std::string reminder = str.substr(pos + 1);
            return run(reminder, start);
        } else if (last == nullptr && (temp->get_id() == -1 || temp->get_token() == "Phi") && error > -1) {
            // Token with an error
            this->out = this->out + "ERROR in symbol  " + str[error] + '\n';
            std::string reminder = str.substr(error + 1);
            return run(reminder, start);
        } else {
            // Token not accepted, may not be reached
            if (str[error] == '!') {
                this->out = this->out + "ERROR in symbol  " + str[error] + '\n';
                std::string reminder = str.substr(error + 1);
                return run(reminder, start);
            } else {
                this->out = this->out + "ERROR in symbol  " + str + '\n';
            }
        }
    }

    return false;
}

