#pragma once
#ifndef TOKENIZER_H
#define TOKENIZER_H
#include <fstream>
#include <string>
#include <map>

using namespace std::string_literals;

class BadToken: public std::runtime_error
{
public:
    BadToken(const std::string& _content)
        : std::runtime_error("bad token: "s + _content)
    {
    }
    BadToken(char _content)
        : std::runtime_error("bad token: "s + _content)
    {
    }
};
struct StateInfo
{
    int label;
    std::string name;
    StateInfo(int _label = -1, std::string _name = "")
        : label(_label)
        , name(_name)
    {
    }
};
class Tokenizer
{
public:
    enum TokenKind
    {
        End = 0,
        Type = 2,
        LSquare = 3,
        RSquare = 4,
        LBraket = 5,
        RBraket = 6,
        Star = 7,
        Comma = 8,
        Number = 9,
        Identifier = 10,
    };
    struct Token
    {
        TokenKind kind;
        std::string content;
    };
protected:
    enum States
    {
        None,
        InName,
        InDigit
    };
    int _lastState;
    std::istream& _file;
    Token _prefetch;
public:
    Tokenizer(std::istream& file)
        : _lastState(None)
        , _file(file)
    {
        prefetch();
    }
    Token get();
    Token peek();
private:
    Token generate_prefetch(const std::string& content);
    void prefetch();
};
#endif