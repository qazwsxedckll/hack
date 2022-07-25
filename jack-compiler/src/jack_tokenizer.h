#ifndef __JACKTOKENIZER_H__
#define __JACKTOKENIZER_H__

#include <gtest/gtest.h>

#include <queue>
#include <unordered_map>

using std::string;
using std::unordered_map;

enum class TokenType { KEYWORD, SYMBOL, IDENTIFIER, INT_CONST, STRING_CONST };
enum class Keyword { CLASS, METHOD, FUNCTION, CONSTRUCTOR, INT, BOOLEAN,
                CHAR, VOID, VAR, STATIC, FIELD, LET, DO, IF, ELSE,
                WHILE, RETURN, K_TRUE, K_FALSE, K_NULL, THIS };

using TokenTypeMap = unordered_map<string, TokenType>;

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
    string current_token() const { return current_token_; }
    static bool ValidIdentifier(const string& symbol);
private:
    FRIEND_TEST(TokenizerTest, ValidIdentifier);
    FRIEND_TEST(TokenizerTest, Advance);

    std::queue<string> tokens_;
    string current_token_;

    static const TokenTypeMap keyword_token_map;
    static const TokenTypeMap symbol_token_map;
    static const unordered_map<string, Keyword> keyword_map;
};
#endif

