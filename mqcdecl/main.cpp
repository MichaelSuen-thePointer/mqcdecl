#include "Tokenizer.h"
#include <iostream>
#include <string>

using Kind = Tokenizer::TokenKind;

void recursive_parse(Tokenizer& lex);

void parse_type_name(Tokenizer& lex)
{
    while (lex.peek().kind != Kind::RBraket)
    {
        recursive_parse(lex);
        if (lex.peek().kind == Kind::Comma)
        {
            lex.get();
            std::cout << ", ";
        }
    }
}

void recursive_parse(Tokenizer& lex)
{
    if (lex.peek().kind != Kind::End)
    {
        auto token = lex.peek();
        switch (token.kind)
        {
        case Kind::Type:
            lex.get();
            recursive_parse(lex);
            std::cout << token.content << ' ';
            break;
        case Kind::LBraket:
            lex.get();
            recursive_parse(lex);
            if (lex.get().kind != Kind::RBraket)
            {
                throw std::exception("syntax error");
            }
            break;
        case Kind::Star:
            lex.get();
            recursive_parse(lex);
            std::cout << "pointer to ";
            break;
        case Kind::Identifier:
            lex.get();
            std::cout << token.content << " is ";
            break;
        default:
            break;
        }
        token = lex.peek();
        switch (token.kind)
        {
        case Kind::LSquare:
        {
            lex.get();
            auto number = lex.get();
            if (number.kind != Kind::Number)
            {
                throw std::exception("syntax error");
            }
            if (lex.get().kind != Kind::RSquare)
            {
                throw std::exception("syntax error");
            }
            std::cout << "array with length " << number.content << " of ";
            break;
        }
        case Kind::LBraket:
            lex.get();
            std::cout << "function accepting ";
            parse_type_name(lex);
            if(lex.get().kind != Tokenizer::RBraket)
            {
                throw std::exception("syntax error");
            }
            std::cout << "returning ";
            break;
        default:
            break;
        }
    }
}

int main()
{
    Tokenizer tokenizer(std::cin);
    /*
    while(tokenizer.peek().kind != Kind::End)
    {
        std::cout << tokenizer.get().content << ' ';
    }
    return 0;
    */
    try
    {
        recursive_parse(tokenizer);
    }
    catch (std::exception& bt)
    {
        std::cerr << " >>" << bt.what() << "<< ";
    }
}
