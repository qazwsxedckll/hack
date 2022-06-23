#ifndef COMPILATION_ENGINE_H_
#define COMPILATION_ENGINE_H_

class CompilationEngine
{
public:
    CompilationEngine();
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