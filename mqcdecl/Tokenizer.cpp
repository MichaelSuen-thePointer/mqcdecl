#include "Tokenizer.h"
#include <set>

void Tokenizer::prefetch()
{
    std::string matched;
    while (_file.peek() != '\n')
    {
        int ch = _file.peek();
        switch (_lastState)
        {
        case None:
        {
            if (isdigit(ch))
            {
                matched.push_back(ch);
                _lastState = InDigit;
            }
            else if (isalpha(ch))
            {
                matched.push_back(ch);
                _lastState = InName;
            }
            else if (isspace(ch))
            {
            }
            else
            {
                switch (ch)
                {
                case '[':
                    _prefetch = {LSquare, "["};
                    break;
                case ']':
                    _prefetch = {RSquare, "]"};
                    break;
                case '(':
                    _prefetch = {LBraket, "("};
                    break;
                case ')':
                    _prefetch = {RBraket, ")"};
                    break;
                case '*':
                    _prefetch = {Star, "*"};
                    break;
                case ',':
                    _prefetch = {Comma, ","};
                    break;
                default:
                    throw BadToken(ch);
                }
                _file.get();
                return;
            }
            _file.get();
            break;
        }//None
        case InName:
        {
            if (isalnum(ch) || ch == '_')
            {
                matched.push_back(ch);
                _file.get();
            }
            else
            {
                _prefetch = generate_prefetch(matched);
                matched.clear();
                _lastState = None;
                return;
            }
            break;
        }
        case InDigit:
        {
            if (isdigit(ch))
            {
                matched.push_back(ch);
                _file.get();
            }
            else
            {
                _prefetch = {Number, matched};
                matched.clear();
                _lastState = None;
                return;
            }
            break;
        }
        }
    }
    if (_lastState != None || matched.length() != 0)
    {
        throw BadToken(matched);
    }
    _prefetch = Token{TokenKind::End, matched};
}

Tokenizer::Token Tokenizer::peek()
{
    return _prefetch;
}

Tokenizer::Token Tokenizer::generate_prefetch(const std::string& content)
{
    const static std::set<std::string> types{
        "int",
        "short",
        "long",
        "double",
        "float",
        "char",
        "void"
    };
    if (types.find(content) != types.end())
    {
        return {Type, content};
    }
    return {Identifier, content};
}

Tokenizer::Token Tokenizer::get()
{
    Token got = _prefetch;
    prefetch();
    return got;
}
