#include "compilation_engine.h"

#include <iostream>

using namespace std;

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

void CompilationEngine::CompileClass() 
{
    output_file_ << "<class>" << endl;

    tokenizer_.advance();
    assert(tokenizer_.tokenType() == TokenType::KEYWORD && tokenizer_.keyWord() == Keyword::CLASS);
    output_file_ << "<keyword> " << kClass << " </keyword>" << endl;

    tokenizer_.advance();
    assert(tokenizer_.tokenType() == TokenType::IDENTIFIER);
    output_file_ << "<identifier> " << tokenizer_.identifier() << " </identifier>" << endl;

    tokenizer_.advance();
    assert(tokenizer_.tokenType() == TokenType::SYMBOL && tokenizer_.symbol() == '{');
    output_file_ << "<symbol> " << tokenizer_.symbol() << " </symbol>" << endl;



    tokenizer_.advance();
    assert(tokenizer_.tokenType() == TokenType::SYMBOL && tokenizer_.symbol() == '}');
    output_file_ << "<symbol> " << tokenizer_.symbol() << " </symbol>" << endl;
    output_file_ << "</class>" << endl;
}