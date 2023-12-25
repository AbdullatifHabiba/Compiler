//
// Created by abdu on 12/19/23.
//

#ifndef COMPILERS_TOKEN_H
#define COMPILERS_TOKEN_H

#include <string>
#include <utility>

using namespace std;
class Token {
public:

    Token() = default;  // Default constructor
    explicit Token(string name1) : name(std::move(name1)) {};
    bool operator == (const Token &rhs) const{
        return name == rhs.name;
    }
    bool operator < (const Token &rhs) const{
        return name < rhs.name;
    }
    ~Token();

    void setName(const std::string& name1);
    [[nodiscard]] const std::string& getName() const;
    bool isTerminal{};


    void setIsTerminal(bool isTerminal);

private:
    string name;

};


#endif //COMPILERS_TOKEN_H
