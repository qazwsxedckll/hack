#ifndef __JACKTOKENIZER_H__
#define __JACKTOKENIZER_H__

#include <fstream>
#include <string>
#include <iostream>
#include <sstream>
#include <unordered_map>

using std::ifstream;
using std::string;
using std::cout;
using std::endl;
using std::stringstream;
using std::unordered_map;

enum TokenType { KEYWORD, SYMBOL, IDENTIFIER, INT_CONST, STRING_CONST };
enum Keyword { CLASS, METHOD, FUNCTION, CONSTRUCTOR, INT, BOOLEAN,
                CHAR, VOID, VAR, STATIC, FIELD, LET, DO, IF, ELSE,
                WHILE, RETURN, K_TRUE, K_FALSE, K_NULL, THIS };

class Jacktokenizer
{
public:
    Jacktokenizer(const string& s);
    bool hasMoreTokens();
    void advance();
    TokenType tokenType();
    Keyword keyWord();
    char symbol();
    string identifier();
    int intVal();
    string stringVal();
    ~Jacktokenizer() {}
private:
    ifstream file_;
    string current_token_;
    stringstream line_stream_;

    unordered_map<string, TokenType> tokentype_map;
    unordered_map<string, Keyword> keyword_map;
};
#endif

