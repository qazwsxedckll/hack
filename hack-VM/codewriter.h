#ifndef __CODEWRITER_H__
#define __CODEWRITER_H__

#include <fstream>
#include <string>
#include <iostream>
#include "parser.h"

using std::string;
using std::ofstream;
using std::cout;
using std::endl;

class CodeWriter
{
public:
    CodeWriter() {};
    void setFileName(const string& filename);
    void writeInit();
    void writeLabel(const string& label);
    void writeGoto(const string& label);
    void writeIf(const string& label);
    void writeCall(const string& functionName, int numArgs);
    void writeReturn();
    void writeFunction(const string& functionName, int numLocals);
    void writeArithmetic(const string& command);
    void writePushPop(const CmdType& command, const string& segment, int index);
    void close();
    ~CodeWriter() {}
private:
    ofstream file_;
    string file_name_prefix_;
    void popUnitary_();
    void popBinary_();
    void pushStack_();
};
#endif
