#ifndef __JACKTOKENIZER_H__
#define __JACKTOKENIZER_H__

#include <gtest/gtest.h>

#include <queue>
#include <unordered_map>

using std::string;
using std::unordered_map;

const string kClass = "class";
const string kConstructor = "constructor";
const string kFunction = "function";
const string kMethod = "method";
const string kField = "field";
const string kStatic = "static";
const string kVar = "var";
const string kInt = "int";
const string kChar = "char";
const string kBoolean = "boolean";
const string kVoid = "void";
const string kTrue = "true";
const string kFalse = "false";
const string kNull = "null";
const string kThis = "this";
const string kLet = "let";
const string kDo = "do";
const string kIf = "if";
const string kElse = "else";
const string kWhile = "while";
const string kReturn = "return";

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
    string current_token() const { return current_token_; }
    ~Jacktokenizer() {}
private:
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

