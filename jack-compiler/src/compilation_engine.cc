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
const string kSubroutineBodyTag = "<subroutineBody>";
const string kSubroutineBodyTagEnd = "</subroutineBody>";
const string kStatementsTag = "<statements> ";
const string kStatementsTagEnd = "</statements>";
const string kExpressionTag = "<expression> ";
const string kExpressionTagEnd = "</expression>";
const string kExpressionListTag = "<expressionList> ";
const string kExpressionListTagEnd = "</expressionList>";
const string kTermTag = "<term> ";
const string kTermTagEnd = "</term>";
const string kLetStatementTag = "<letStatement> ";
const string kLetStatementTagEnd = "</letStatement>";
const string kDoStatementTag = "<doStatement> ";
const string kDoStatementTagEnd = "</doStatement>";
const string kReturnStatementTag = "<returnStatement> ";
const string kReturnStatementTagEnd = "</returnStatement>";
const string kIfStatementTag = "<ifStatement> ";
const string kIfStatementTagEnd = "</ifStatement>";

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

    tokenizer_.advance();
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

void CompilationEngine::CompileSymbol(const char symbol)
{
    if (tokenizer_.symbol() == symbol)
    {
        output_file_ << indent_ << kSymbolTag << tokenizer_.current_token() << kSymbolTagEnd << endl;
        tokenizer_.advance();
    }
    else
    {
        cout << "want symbol: " << symbol << endl;
        WrongSymbol();
    }
}

void CompilationEngine::CompileKeyword(const Keyword& keyword)
{
    if (tokenizer_.keyWord() == keyword)
    {
        output_file_ << indent_ << kKeywordTag << tokenizer_.current_token() << kKeywordTagEnd << endl;
        tokenizer_.advance();
    }
    else
    {
        cout << "want keyword: " << int(keyword) << endl;
        WrongKeyword();
    }
}

void CompilationEngine::CompileIdentifier()
{
    if (tokenizer_.tokenType() == TokenType::IDENTIFIER)
    {
        output_file_ << indent_ << kIdentifierTag << tokenizer_.identifier() << kIdentifierTagEnd << endl;
        tokenizer_.advance();
    }
    else
    {
        WrongTokenType();
    }
}

void CompilationEngine::CompileType()
{
    if (tokenizer_.tokenType() == TokenType::KEYWORD)
    {
        if (tokenizer_.keyWord() == Keyword::INT)
        {
            output_file_ << indent_ << kKeywordTag << kInt << kKeywordTagEnd << endl;
            tokenizer_.advance();
        }
        else if (tokenizer_.keyWord() == Keyword::CHAR)
        {
            output_file_ << indent_ << kKeywordTag << kChar << kKeywordTagEnd << endl;
            tokenizer_.advance();
        }
        else if (tokenizer_.keyWord() == Keyword::BOOLEAN)
        {
            output_file_ << indent_ << kKeywordTag << kBoolean << kKeywordTagEnd << endl;
            tokenizer_.advance();
        }
        else
        {
            WrongKeyword();
        }
    }
    else if (tokenizer_.tokenType() == TokenType::IDENTIFIER)
    {
        output_file_ << indent_ << kIdentifierTag << tokenizer_.identifier() << kIdentifierTagEnd << endl;
        tokenizer_.advance();
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
    CompileSymbol('{');

    // classVarDec*
    while (tokenizer_.tokenType() == TokenType::KEYWORD
            && (tokenizer_.keyWord() == Keyword::STATIC
                || tokenizer_.keyWord() == Keyword::FIELD))
    {
        CompileClassVarDec();
    }

    // subroutineDec*
    while (tokenizer_.tokenType() == TokenType::KEYWORD
            && (tokenizer_.keyWord() == Keyword::CONSTRUCTOR
                || tokenizer_.keyWord() == Keyword::FUNCTION
                || tokenizer_.keyWord() == Keyword::METHOD))
    {
        CompileSubroutine();
    }

    // '}'
    CompileSymbol('}');
    indent_ = indent_.substr(0, indent_.length() - 2);
    output_file_ << kClassTagEnd << endl;
}

void CompilationEngine::CompileClassVarDec()
{
    output_file_ << indent_ << kClassVarDecTag << endl;
    indent_ += "  ";
    
    // ('static' | 'field')
    if (tokenizer_.keyWord() == Keyword::STATIC)
    {
        output_file_ << indent_ << kKeywordTag << kStatic << kKeywordTagEnd << endl;
        tokenizer_.advance();
    }
    else if (tokenizer_.keyWord() == Keyword::FIELD)
    {
        output_file_ << indent_ << kKeywordTag << kField << kKeywordTagEnd << endl;
        tokenizer_.advance();
    }
    else
    {
        WrongKeyword();
    }

    // type
    CompileType();

    // varName
    CompileIdentifier();

    // (',' varName)*
    while (tokenizer_.tokenType() == TokenType::SYMBOL && tokenizer_.symbol() == ',')
    {
        output_file_ << indent_ << kSymbolTag << tokenizer_.symbol() << kSymbolTagEnd << endl;
        tokenizer_.advance();
        CompileIdentifier();
    }

    // ';'
    CompileSymbol(';');

    indent_ = indent_.substr(0, indent_.length() - 2);
    output_file_ << indent_ << kClassVarDecTagEnd << endl;
}

void CompilationEngine::CompileSubroutine()
{
    output_file_ << indent_ << kSubroutineDecTag << endl;
    indent_ += "  ";

    // ('constructor' | 'function' | 'method')
    if (tokenizer_.keyWord() == Keyword::CONSTRUCTOR)
    {
        output_file_ << indent_ << kKeywordTag << kConstructor << kKeywordTagEnd << endl;
        tokenizer_.advance();
    }
    else if (tokenizer_.keyWord() == Keyword::FUNCTION)
    {
        output_file_ << indent_ << kKeywordTag << kFunction << kKeywordTagEnd << endl;
        tokenizer_.advance();
    }
    else if (tokenizer_.keyWord() == Keyword::METHOD)
    {
        output_file_ << indent_ << kKeywordTag << kMethod << kKeywordTagEnd << endl;
        tokenizer_.advance();
    }
    else
    {
        WrongKeyword();
    }

    // ('void' | type)
    if (tokenizer_.tokenType() == TokenType::KEYWORD)
    {
        if (tokenizer_.keyWord() == Keyword::VOID)
        {
            output_file_ << indent_ << kKeywordTag << kVoid << kKeywordTagEnd << endl;
            tokenizer_.advance();
        }
        else
        {
            WrongKeyword();
        }
    }
    else
    {
        CompileType();
    }

    // subroutineName
    CompileIdentifier();

    // '('
    CompileSymbol('(');

    // parameterList
    CompileParameterList();

    // ')'
    CompileSymbol(')');

    // subroutineBody:
    output_file_ << indent_ << kSubroutineBodyTag << endl;
    indent_ += "  ";
    // '{'
    CompileSymbol('{');

    // varDec*
    while (tokenizer_.tokenType() == TokenType::KEYWORD
        && tokenizer_.keyWord() == Keyword::VAR)
    {
        CompileVarDec();
    }
    // statements
    CompileStatements();
    // '}'
    CompileSymbol('}');
    indent_ = indent_.substr(0, indent_.length() - 2);
    output_file_ << indent_ << kSubroutineBodyTagEnd << endl;

    indent_ = indent_.substr(0, indent_.length() - 2);
    output_file_ << indent_ << kSubroutineDecTagEnd << endl;
}

void CompilationEngine::CompileParameterList()
{
    output_file_ << indent_ << kParameterListTag << endl;
    indent_ += "  ";

    if (tokenizer_.tokenType() != TokenType::SYMBOL)
    {
        CompileType();
        CompileIdentifier();
        while (true)
        {
            if (tokenizer_.symbol() == ',')
            {
                output_file_ << kSymbolTag << tokenizer_.current_token() << kSymbolTagEnd << endl;
                tokenizer_.advance();
                CompileType();
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
    CompileType();
    // varName
    CompileIdentifier();
    // (',' varName)*
    while (tokenizer_.tokenType() == TokenType::SYMBOL
        && tokenizer_.symbol() == ',')
    {
        CompileSymbol(',');
        CompileIdentifier();
    }
    CompileSymbol(';');

    indent_ = indent_.substr(0, indent_.length() - 2);
    output_file_ << indent_ << kVarDecTagEnd << endl;
}

void CompilationEngine::CompileStatements()
{
    output_file_ << indent_ << kStatementsTag << endl;
    indent_ += "  ";

    // statement*
    while (true)
    {
        if (tokenizer_.tokenType() == TokenType::KEYWORD)
        {
            if (tokenizer_.keyWord() == Keyword::LET)
            {
                CompileLet();
            }
            else if (tokenizer_.keyWord() == Keyword::IF)
            {
                // CompileIf();
                break;
            }
            else if (tokenizer_.keyWord() == Keyword::WHILE)
            {
                // CompileWhile();
                break;
            }
            else if (tokenizer_.keyWord() == Keyword::DO)
            {
                CompileDo();
            }
            else if (tokenizer_.keyWord() == Keyword::RETURN)
            {
                CompileReturn();
            }
            else
            {
                cout << "wrong keyword: " << int(tokenizer_.keyWord()) << endl;
                exit(1);
            }
        }
        else
        {
            break;
        }
    }
    
    indent_ = indent_.substr(0, indent_.length() - 2);
    output_file_ << indent_ << kStatementsTagEnd << endl;
}


void CompilationEngine::CompileDo()
{
    output_file_ << indent_ << kDoStatementTag << endl;
    indent_ += "  ";

    // 'do'
    CompileKeyword(Keyword::DO);

    // subroutineCall:
    // subroutineName '(' expressionList ')' | (className | varName) '.' subroutineName '(' expressionList ')'
    CompileIdentifier();
    if (tokenizer_.symbol() == '(')
    {
        // '('
        CompileSymbol('(');
        // expressionList
        CompileExpressionList();
        // ')'
        CompileSymbol(')');
    }
    else if (tokenizer_.symbol() == '.')
    {
        // '.'
        CompileSymbol('.');
        // subroutineName
        CompileIdentifier();
        // '('
        CompileSymbol('(');
        // expressionList
        CompileExpressionList();
        // ')'
        CompileSymbol(')');
    }
    else
    {
        WrongSymbol();
    }

    // ';'
    CompileSymbol(';');

    indent_ = indent_.substr(0, indent_.length() - 2);
    output_file_ << indent_ << kDoStatementTagEnd << endl;
}

void CompilationEngine::CompileLet()
{
    output_file_ << indent_ << kLetStatementTag << endl;
    indent_ += "  ";

    // 'let'
    CompileKeyword(Keyword::LET);

    // varName
    CompileIdentifier();

    // ('[' expression ']')?
    if (tokenizer_.tokenType() == TokenType::SYMBOL
        && tokenizer_.symbol() == '[')
    {
        CompileSymbol('[');
        CompileExpression();
        CompileSymbol(']');
    }

    // '='
    CompileSymbol('=');
    // expression
    CompileExpression();
    // ';'
    CompileSymbol(';');

    indent_ = indent_.substr(0, indent_.length() - 2);
    output_file_ << indent_ << kLetStatementTagEnd << endl;

}

void CompilationEngine::CompileWhile()
{

}

void CompilationEngine::CompileReturn()
{
    output_file_ << indent_ << kReturnStatementTag << endl;
    indent_ += "  ";

    // 'return'
    CompileKeyword(Keyword::RETURN);

    // expression?
    if (!(tokenizer_.tokenType() == TokenType::SYMBOL && tokenizer_.symbol() == ';'))
    {
        CompileExpression();
    }

    // ';'
    CompileSymbol(';');

    indent_ = indent_.substr(0, indent_.length() - 2);
    output_file_ << indent_ << kReturnStatementTagEnd << endl;

}

void CompilationEngine::CompileIf()
{
    output_file_ << indent_ << kIfStatementTag << endl;
    indent_ += "  ";

    indent_ = indent_.substr(0, indent_.length() - 2);
    output_file_ << indent_ << kIfStatementTagEnd << endl;
}

void CompilationEngine::CompileExpression()
{
    output_file_ << indent_ << kExpressionTag << endl;
    indent_ += "  ";

    // term (op term)*
    CompileTerm();

    indent_ = indent_.substr(0, indent_.length() - 2);
    output_file_ << indent_ << kExpressionTagEnd << endl;
}

void CompilationEngine::CompileTerm()
{
    output_file_ << indent_ << kTermTag << endl;
    indent_ += "  ";

    CompileIdentifier();

    indent_ = indent_.substr(0, indent_.length() - 2);
    output_file_ << indent_ << kTermTagEnd << endl;
}

void CompilationEngine::CompileExpressionList()
{
    output_file_ << indent_ << kExpressionListTag << endl;
    indent_ += "  ";

    indent_ = indent_.substr(0, indent_.length() - 2);
    output_file_ << indent_ << kExpressionListTagEnd << endl;
}