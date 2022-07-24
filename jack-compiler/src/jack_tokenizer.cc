#include "jack_tokenizer.h"

#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>

using std::ifstream;
using std::stringstream;
using std::cout;
using std::endl;

const unordered_map<string, TokenType> Jacktokenizer::keyword_token_map = {
    {"class", TokenType::KEYWORD},
    {"constructor", TokenType::KEYWORD},
    {"function", TokenType::KEYWORD},
    {"method", TokenType::KEYWORD},
    {"field", TokenType::KEYWORD},
    {"static", TokenType::KEYWORD},
    {"var", TokenType::KEYWORD},
    {"int", TokenType::KEYWORD},
    {"char", TokenType::KEYWORD},
    {"boolean", TokenType::KEYWORD},
    {"void", TokenType::KEYWORD},
    {"true", TokenType::KEYWORD},
    {"false", TokenType::KEYWORD},
    {"null", TokenType::KEYWORD},
    {"this", TokenType::KEYWORD},
    {"let", TokenType::KEYWORD},
    {"do", TokenType::KEYWORD},
    {"if", TokenType::KEYWORD},
    {"else", TokenType::KEYWORD},
    {"while", TokenType::KEYWORD},
    {"return", TokenType::KEYWORD}};

const unordered_map<string, TokenType> Jacktokenizer::symbol_token_map = {
    {"{", TokenType::SYMBOL},
    {"}", TokenType::SYMBOL},
    {"(", TokenType::SYMBOL},
    {")", TokenType::SYMBOL},
    {"[", TokenType::SYMBOL},
    {"]", TokenType::SYMBOL},
    {".", TokenType::SYMBOL},
    {",", TokenType::SYMBOL},
    {";", TokenType::SYMBOL},
    {"+", TokenType::SYMBOL},
    {"-", TokenType::SYMBOL},
    {"*", TokenType::SYMBOL},
    {"/", TokenType::SYMBOL},
    {"&", TokenType::SYMBOL},
    {"|", TokenType::SYMBOL},
    {"<", TokenType::SYMBOL},
    {">", TokenType::SYMBOL},
    {"=", TokenType::SYMBOL},
    {"~", TokenType::SYMBOL}};

const unordered_map<string, Keyword> Jacktokenizer::keyword_map = {
    {"class", Keyword::CLASS},
    {"constructor", Keyword::CONSTRUCTOR},
    {"function", Keyword::FUNCTION},
    {"method", Keyword::METHOD},
    {"field", Keyword::FIELD},
    {"static", Keyword::STATIC},
    {"var", Keyword::VAR},
    {"int", Keyword::INT},
    {"char", Keyword::CHAR},
    {"boolean", Keyword::BOOLEAN},
    {"void", Keyword::VOID},
    {"true", Keyword::K_TRUE},
    {"false", Keyword::K_FALSE},
    {"null", Keyword::K_NULL},
    {"this", Keyword::THIS},
    {"let", Keyword::LET},
    {"do", Keyword::DO},
    {"if", Keyword::IF},
    {"else", Keyword::ELSE},
    {"while", Keyword::WHILE},
    {"return", Keyword::RETURN}};

const string kSymbolToken = "{}()[].,;+-*/&|<>=~";

Jacktokenizer::Jacktokenizer(const string &s)
{
    ifstream file(s);
    if (!file)
    {
        cout << "Jacktokenizer: Failed to open file(" << s << ")" << endl;
        exit(1);
    }

    string current_line;
    bool comment_found = false;
    string::size_type comment_start, comment_end;
    while (getline(file, current_line))
    {
        // inside comment
        if (comment_found == true)
        {
            comment_end = current_line.find("*/");
            if (comment_end == string::npos)
            {
                continue;
            }
            else
            {
                comment_found = false;
                current_line.erase(0, comment_end + 2);
            }
        }

        // remove //comment
        comment_start = current_line.find("//");
        if (comment_start != string::npos)
        {
            current_line.erase(comment_start);
        }

        // remove /* comments
        comment_start = current_line.find("/*");
        if (comment_start != string::npos)
        {
            comment_found = true;
            comment_end = current_line.find("*/");
            if (comment_end != string::npos)
            {
                comment_found = false;
                current_line.erase(comment_start, comment_end - comment_start + 2);
            }
            else
            {
                current_line.erase(comment_start);
                continue;
            }
        }

        stringstream ss(current_line);
        string word;
        while (ss >> word)
        {
            string::size_type start_pos{0};
            while (start_pos < word.size())
            {
                auto symbol_pos{word.find_first_of(kSymbolToken, start_pos)};
                if (symbol_pos != string::npos)
                {
                    string part{word.substr(start_pos, symbol_pos - start_pos)};
                    if (!part.empty())
                    {
                        tokens.push(part);
                    }
                    tokens.push(word.substr(symbol_pos, 1));
                    start_pos = symbol_pos + 1;
                }
                else
                {
                    tokens.push(word.substr(start_pos));
                    break;
                }
            }
        }
    }
}

bool Jacktokenizer::hasMoreTokens()
{
    return !tokens.empty();
}

void Jacktokenizer::advance()
{
    current_token_ = tokens.front();
    tokens.pop();
}

TokenType Jacktokenizer::tokenType()
{
    // // keyword & symbol
    // auto token_type = tokentype_map.find(current_token_);
    // if (token_type != tokentype_map.end())
    // {
    //     return token_type->second;
    // }
    // // string constant
    // else if (current_token_.front() == '"' && current_token_.back() == '"')
    // {
    //     if (current_token_.find("\n", 1) != string::npos || current_token_.find("\"", 1, current_token_.length() - 2))
    //     {
    //         cout << "Jacktokenizer::tokenType: Invalid string constant(" << current_token_ << ")" << endl;
    //         exit(1);
    //     }
    //     else
    //     {
    //         return TokenType::STRING_CONST;
    //     }
    // }
    // else if (std::all_of(current_token_.begin(), current_token_.end(), ::isdigit))
    // {
    //     int i = std::stoi(current_token_);
    //     if (i >= 0 && i <= 32767)
    //     {
    //         return TokenType::INT_CONST;
    //     }
    //     else
    //     {
    //         cout << "Jacktokenizer::tokenType: Invalid int constant(" << current_token_ << ")" << endl;
    //         exit(1);
    //     }
    // }
    // else if (!std::isdigit(current_token_.front()))
    // {
    //     return TokenType::IDENTIFIER;
    // }
    // else
    // {
    //     cout << "Jacktokenizer::tokenType: Invalid token(" << current_token_ << ")" << endl;
    //     exit(1);
    // }

    return TokenType::IDENTIFIER;
}

Keyword Jacktokenizer::keyWord()
{
    if (tokenType() == TokenType::KEYWORD)
    {
        return keyword_map.at(current_token_);
    }
    else
    {
        cout << "Jacktokenizer::keyWord: Invalid token(" << current_token_ << ")" << endl;
        exit(1);
    }
}

char Jacktokenizer::symbol()
{
    if (tokenType() == TokenType::SYMBOL)
    {
        return current_token_.front();
    }
    else
    {
        cout << "Jacktokenizer::symbol: Invalid token(" << current_token_ << ")" << endl;
        exit(1);
    }
}

string Jacktokenizer::identifier()
{
    if (tokenType() == TokenType::IDENTIFIER)
    {
        return current_token_;
    }
    else
    {
        cout << "Jacktokenizer::identifier: Invalid token(" << current_token_ << ")" << endl;
        exit(1);
    }
}

int Jacktokenizer::intVal()
{
    if (tokenType() == TokenType::INT_CONST)
    {
        return std::stoi(current_token_);
    }
    else
    {
        cout << "Jacktokenizer::intVal: Invalid token(" << current_token_ << ")" << endl;
        exit(1);
    }
}

string Jacktokenizer::stringVal()
{
    if (tokenType() == TokenType::STRING_CONST)
    {
        return current_token_;
    }
    else
    {
        cout << "Jacktokenizer::stringVal: Invalid token(" << current_token_ << ")" << endl;
        exit(1);
    }
}
