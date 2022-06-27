#ifndef COMPILATION_ENGINE_H_
#define COMPILATION_ENGINE_H_

#include <fstream>

class CompilationEngine
{
public:
    CompilationEngine(std::ifstream input_file, std::ofstream output_file);
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
    ~CompilationEngine();
private:
};

#endif // !COMPILATION_ENGINE_H_