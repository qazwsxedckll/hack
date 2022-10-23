#ifndef COMPILATION_ENGINE_H_
#define COMPILATION_ENGINE_H_

#include "jack_tokenizer.h"

#include <fstream>

class CompilationEngine
{
public:
    CompilationEngine(const std::string& input, const std::string& output);
    void CompileClass();
    void CompileClassVarDec();
    void CompileSubroutine();
    void CompileParameterList();
    void CompileVarDec();
    void CompileStatements();
    void CompileDo();
    void CompileLet();
    void CompileWhile();
    void CompileReturn();
    void CompileIf();
    void CompileExpression();
    void CompileTerm();
    void CompileExpressionList();
    ~CompilationEngine() {};
private:
    void CompileType();
    void CompileIdentifier();
    void CompileSymbol(const char symbol);
    void CompileKeyword(const Keyword& keyword);
    void WrongKeyword();
    void WrongTokenType();
    void WrongSymbol();
    std::ifstream input_file_;
    std::ofstream output_file_;

    string indent_;

    Jacktokenizer tokenizer_;
};

#endif // !COMPILATION_ENGINE_H_