#include "compilation_engine.h"

#include <iostream>

using namespace std;

const string kClassTag = "<class>";
const string kClassTagEnd = "</class>";
const string kClassVarDecTag = "<classVarDec>";
const string kClassVarDecTagEnd = "</classVarDec>";
const string kVarDecTag = "<varDec>";
const string kVarDecTagEnd = "</varDec>";
const string kParameterListTag = "<parameterList>";
const string kParameterListTagEnd = "</parameterList>";
const string kSubroutineDecTag = "<subroutineDec>";
const string kSubroutineDecTagEnd = "</subroutineDec>";
const string kKeywordTag = "<keyword> ";
const string kKeywordTagEnd = " </keyword>";
const string kIdentifierTag = "<identifier> ";
const string kIdentifierTagEnd = " </identifier>";
const string kSymbolTag = "<symbol> ";
const string kSymbolTagEnd = " </symbol>";

CompilationEngine::CompilationEngine(const string& input, const string& output) :
    input_file_(input),
    output_file_(output),
    tokenizer_(input)
{
    if (!output_file_) {
        cout << "Jacktokenizer: Failed to open file(" << output << ")" << endl;
        exit(1);
    }

    CompileClass();
}

void CompilationEngine::WrongKeyword()
{
    cout << "wrong keyword: " << int(tokenizer_.keyWord()) << endl;
    exit(1);
}

void CompilationEngine::WrongTokenType()
{
    cout << "wrong token type: " << int(tokenizer_.tokenType()) << endl;
    exit(1);
}

void CompilationEngine::WrongSymbol()
{
    cout << "wrong symbol: " << int(tokenizer_.symbol()) << endl;
    exit(1);
}

void CompilationEngine::CompileSymbol(const char symbol, bool advance)
{
    if (advance)
    {
        tokenizer_.advance();
    }
    if (tokenizer_.symbol() == symbol)
    {
        output_file_ << indent_ << kSymbolTag << tokenizer_.current_token() << kSymbolTagEnd << endl;
    }
    else
    {
        cout << "want symbol: " << symbol << endl;
        WrongSymbol();
    }
}

void CompilationEngine::CompileKeyword(const Keyword& keyword) 
{
    tokenizer_.advance();
    if (tokenizer_.keyWord() == keyword)
    {
        output_file_ << indent_ << kKeywordTag << tokenizer_.current_token() << kKeywordTagEnd << endl;
    }
    else
    {
        cout << "want keyword: " << int(keyword) << endl;
        WrongKeyword();
    }
}

void CompilationEngine::CompileIdentifier()
{
    tokenizer_.advance();
    if (tokenizer_.tokenType() == TokenType::IDENTIFIER)
    {
        output_file_ << indent_ << kIdentifierTag << tokenizer_.identifier() << kIdentifierTagEnd << endl;
    }
    else
    {
        WrongTokenType();
    }
}

void CompilationEngine::CompileType(bool advance)
{
    if (advance)
    {
        tokenizer_.advance();
    }

    if (tokenizer_.tokenType() == TokenType::KEYWORD)
    {
        if (tokenizer_.keyWord() == Keyword::INT)
        {
            output_file_ << indent_ << kKeywordTag << kInt << kKeywordTagEnd << endl;
        }
        else if (tokenizer_.keyWord() == Keyword::CHAR)
        {
            output_file_ << indent_ << kKeywordTag << kChar << kKeywordTagEnd << endl;
        }
        else if (tokenizer_.keyWord() == Keyword::BOOLEAN)
        {
            output_file_ << indent_ << kKeywordTag << kBoolean << kKeywordTagEnd << endl;
        }
        else
        {
            WrongKeyword();
        }
    }
    else if (tokenizer_.tokenType() == TokenType::IDENTIFIER)
    {
        output_file_ << indent_ << kIdentifierTag << tokenizer_.identifier() << kIdentifierTagEnd << endl;
    }
    else
    {
        WrongTokenType();
    }
}

void CompilationEngine::CompileClass() 
{
    output_file_ << indent_ << kClassTag << endl;
    indent_ += "  ";

    // 'class'
    CompileKeyword(Keyword::CLASS);

    // className
    CompileIdentifier();

    // '{'
    CompileSymbol('{', true);

    CompileClassVarDec();
    CompileSubroutine();

    // tokenizer_.advance();
    // assert(tokenizer_.tokenType() == TokenType::SYMBOL && tokenizer_.symbol() == '}');
    // output_file_ << kSymbolTag << tokenizer_.symbol() << kSymbolTagEnd << endl;
    indent_ = indent_.substr(0, indent_.length() - 2);
    output_file_ << kClassTagEnd << endl;
}

void CompilationEngine::CompileClassVarDec()
{
    output_file_ << indent_ << kClassVarDecTag << endl;
    indent_ += "  ";
    
    // ('static' | 'field')
    tokenizer_.advance();
    if (tokenizer_.keyWord() == Keyword::STATIC)
    {
        output_file_ << indent_ << kKeywordTag << kStatic << kKeywordTagEnd << endl;
    }
    else if (tokenizer_.keyWord() == Keyword::FIELD)
    {
        output_file_ << indent_ << kKeywordTag << kField << kKeywordTagEnd << endl;
    }
    else
    {
        WrongKeyword();
    }

    // type
    CompileType(true);

    // varName
    CompileIdentifier();

    // (',' varName)* ';'
    tokenizer_.advance();
    if (tokenizer_.tokenType() == TokenType::SYMBOL)
    {
        while (true)
        {
            if (tokenizer_.symbol() == ',')
            {
                output_file_ << indent_ << kSymbolTag << tokenizer_.symbol() << kSymbolTagEnd << endl;
                CompileIdentifier();
            }
            else if (tokenizer_.symbol() == ';')
            {
                output_file_ << indent_ << kSymbolTag << tokenizer_.symbol() << kSymbolTagEnd << endl;
                break;
            }
            else
            {
                WrongSymbol();
            }
        }
    }

    indent_ = indent_.substr(0, indent_.length() - 2);
    output_file_ << indent_ << kClassVarDecTagEnd << endl;
}

void CompilationEngine::CompileSubroutine()
{
    output_file_ << indent_ << kSubroutineDecTag << endl;
    indent_ += "  ";

    // ('constructor' | 'function' | 'method')
    tokenizer_.advance();
    if (tokenizer_.keyWord() == Keyword::CONSTRUCTOR)
    {
        output_file_ << indent_ << kKeywordTag << kConstructor << kKeywordTagEnd << endl;
    }
    else if (tokenizer_.keyWord() == Keyword::FUNCTION)
    {
        output_file_ << indent_ << kKeywordTag << kFunction << kKeywordTagEnd << endl;
    }
    else if (tokenizer_.keyWord() == Keyword::METHOD)
    {
        output_file_ << indent_ << kKeywordTag << kMethod << kKeywordTagEnd << endl;
    }
    else
    {
        WrongKeyword();
    }

    // ('void' | type)
    tokenizer_.advance();
    if (tokenizer_.tokenType() == TokenType::KEYWORD)
    {
        if (tokenizer_.keyWord() == Keyword::VOID)
        {
            output_file_ << indent_ << kKeywordTag << kVoid << kKeywordTagEnd << endl;
        }
        else
        {
            WrongKeyword();
        }
    }
    else
    {
        CompileType(false);
    }

    // subroutineName
    CompileIdentifier();

    // '('
    CompileSymbol('(', true);

    // parameterList
    CompileParameterList();

    // ')'
    CompileSymbol(')', false);

    // subroutineBody: '{' varDec* statements '}'
    CompileSymbol('{', true);
    CompileVarDec();
    CompileSymbol('}', true);


    indent_ = indent_.substr(0, indent_.length() - 2);
    output_file_ << indent_ << kSubroutineDecTagEnd << endl;
}

void CompilationEngine::CompileParameterList()
{
    output_file_ << indent_ << kParameterListTag << endl;
    indent_ += "  ";

    tokenizer_.advance();
    if (tokenizer_.tokenType() != TokenType::SYMBOL)
    {
        CompileType(true);
        CompileIdentifier();
        while (true)
        {
            tokenizer_.advance();
            if (tokenizer_.symbol() == ',')
            {
                output_file_ << kSymbolTag << tokenizer_.current_token() << kSymbolTagEnd << endl;
                CompileType(true);
                CompileIdentifier();
            }
            else
            {
                break;
            }
        }
    }

    indent_ = indent_.substr(0, indent_.length() - 2);
    output_file_ << indent_ << kParameterListTagEnd << endl;
}

void CompilationEngine::CompileVarDec()
{
    output_file_ << indent_ << kVarDecTag << endl;
    indent_ += "  ";

    // 'var'
    CompileKeyword(Keyword::VAR);
    // type
    CompileType(true);
    // varName
    CompileIdentifier();
    // (',' varName)*
    while (true)
    {
        tokenizer_.advance();
        if (tokenizer_.symbol() == ',')
        {
            output_file_ << kSymbolTag << tokenizer_.current_token() << kSymbolTagEnd << endl;
            CompileIdentifier();
        }
        else
        {
            break;
        }
    }
    CompileSymbol(';', false);

    indent_ = indent_.substr(0, indent_.length() - 2);
    output_file_ << indent_ << kVarDecTagEnd << endl;
}