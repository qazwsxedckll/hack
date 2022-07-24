#ifndef __JACKTOKENIZER_H__
#define __JACKTOKENIZER_H__

#include <queue>
#include <unordered_map>

using std::string;
using std::unordered_map;

enum class TokenType { KEYWORD, SYMBOL, IDENTIFIER, INT_CONST, STRING_CONST };
enum class Keyword { CLASS, METHOD, FUNCTION, CONSTRUCTOR, INT, BOOLEAN,
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
    string current_token() const { return current_token_; }
    ~Jacktokenizer() {}
private:
    std::queue<string> tokens;
    string current_token_;

    static const unordered_map<string, TokenType> keyword_token_map;
    static const unordered_map<string, TokenType> symbol_token_map;
    static const unordered_map<string, Keyword> keyword_map;
};
#endif

