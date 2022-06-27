#ifndef COMPILATION_ENGINE_H_
#define COMPILATION_ENGINE_H_

#include <fstream>

class CompilationEngine
{
public:
    CompilationEngine(const std::string& input, const std::string& output);
    void CompileClass();
    void CompileClassVarDec();
    void CompileSubroutine();
    void CompileParameterList();
    void CompileCarDec();
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
    std::ifstream input_file_;
    std::ofstream output_file_;
};

#endif // !COMPILATION_ENGINE_H_