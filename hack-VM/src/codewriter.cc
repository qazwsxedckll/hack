#include "codewriter.h"

void CodeWriter::setFileName(const string& filename)
{
    string::size_type slash_pos, dot_pos;
    slash_pos = filename.find_last_of("/");
    dot_pos = filename.find_last_of(".");
    file_name_prefix_ = filename.substr(slash_pos + 1, dot_pos - slash_pos - 1);
}

void CodeWriter::writeInit()
{
    file_ << "@256" << endl //SP=256
        << "D=A" << endl
        << "@SP" << endl
        << "M=D" << endl;
    writeCall("Sys.init", 0);
        /* << "@Sys.init" << endl */
        /* << "0;JMP" << endl; */
}

void CodeWriter::writeArithmetic(const string& command)
{
    if (command.compare("add") == 0) {
        popBinary_();
        file_ << "M=D+M" << endl;
    } else if (command.compare("sub") == 0) {
        popBinary_();
        file_ << "M=M-D" << endl;
    } else if (command.compare("neg") == 0) {
        file_ << "@SP" << endl
            << "A=M-1" << endl
            << "M=-M" << endl;
    } else if (command.compare("and") == 0) {
        popBinary_();
        file_ << "M=D&M" << endl;
    } else if (command.compare("or") == 0) {
        popBinary_();
        file_ << "M=D|M" << endl;
    } else if (command.compare("not") == 0) {
        file_ << "@SP" << endl
            << "A=M-1" << endl
            << "M=!M" << endl;
    } else {
        static int jmp = 1;
        string condition;
        if (command.compare("eq") == 0) {
            condition = "D;JEQ";
        } else if (command.compare("gt") == 0) {
            condition = "D;JLT";
        } else if (command.compare("lt") == 0) {
            condition = "D;JGT";
        } else {
            cout << "CodeWriter::writeArithmetic: Invalid syntax" << endl;
            exit(1);
        }
        popBinary_();
        file_ << "D=D-M" << endl
            << "@JMP" << jmp << endl
            << condition << endl
            << "@SP" << endl
            << "A=M-1" << endl
            << "M=0" << endl
            << "@JMPEND" << jmp << endl
            << "0;JMP" << endl
            << "(JMP" << jmp << ")" << endl
            << "@SP" << endl
            << "A=M-1" << endl
            << "M=-1" << endl
            << "(JMPEND" << jmp << ")" << endl;
        jmp++;
    }
}

void CodeWriter::writePushPop(const CmdType& command, const string& segment, int index)
{
    if (command == C_PUSH) {
        if (segment.compare("constant") == 0){
            file_ << "@" << index << endl
                << "D=A" << endl;
        } else if (segment.compare("static") == 0) {
            file_ << "@" << file_name_prefix_ << "." << index << endl
                << "D=M" << endl;
        } else {
            if (segment.compare("local") == 0) {
                file_ << "@LCL" << endl
                    << "D=M" << endl;
            } else if (segment.compare("argument") == 0) {
                file_ << "@ARG" << endl
                    << "D=M" << endl;
            } else if (segment.compare("this") == 0) {
                file_ << "@THIS" << endl
                    << "D=M" << endl;
            } else if (segment.compare("that") == 0) {
                file_ << "@THAT" << endl
                    << "D=M" << endl;
            } else if (segment.compare("temp") == 0) {
                file_ << "@R5" << endl
                    << "D=A" << endl;
            } else if (segment.compare("pointer") == 0) {
                file_ << "@R3" << endl
                    << "D=A" << endl;
            } else {
                cout << "CodeWriter::writePushPop: Invalid syntax in push" << endl;
                exit(1);
            }
            file_ << "@" << index << endl
                << "A=D+A" << endl
                << "D=M" << endl;
        }
        pushStack_();
    }else if (command == C_POP) {
        popUnitary_();
        file_ << "@R14" << endl
            << "M=D" << endl;

        if (segment.compare("local") == 0) {
            file_ << "@LCL" << endl
                << "D=M" << endl
                << "@" << index << endl
                << "D=D+A" << endl;
        } else if (segment.compare("argument") == 0) {
            file_ << "@ARG" << endl
                << "D=M" << endl
                << "@" << index << endl
                << "D=D+A" << endl;
        } else if (segment.compare("this") == 0) {
            file_ << "@THIS" << endl
                << "D=M" << endl
                << "@" << index << endl
                << "D=D+A" << endl;
        } else if (segment.compare("that") == 0) {
            file_ << "@THAT" << endl
                << "D=M" << endl
                << "@" << index << endl
                << "D=D+A" << endl;
        } else if (segment.compare("temp") == 0) {
            file_ << "@R5" << endl
                << "D=A" << endl
                << "@" << index << endl
                << "D=D+A" << endl;
        } else if (segment.compare("pointer") == 0) {
            file_ << "@R3" << endl
                << "D=A" << endl
                << "@" << index << endl
                << "D=D+A" << endl;
        } else if (segment.compare("static") == 0) {
            file_ << "@" << file_name_prefix_ << "." << index << endl
                << "D=A" << endl;
        } else {
            cout << "CodeWriter::writePushPop: Invalid syntax in pop" << endl;
            exit(1);
        }
        file_ << "@R15" << endl
            << "M=D" << endl
            << "@R14" << endl
            << "D=M" << endl
            << "@R15" << endl
            << "A=M" << endl
            << "M=D" << endl;
    }
}

void CodeWriter::writeLabel(const string& label)
{
    if (isdigit(label[0])) {
        cout << "CodeWriter::writeLable: Label starts with digit" << endl;
        exit(1);
    }
    file_ << "(" << function_name_ << "$" << label << ")" << endl;
}

void CodeWriter::writeGoto(const string& label)
{
    file_ << "@" << function_name_ << "$" << label << endl
        << "0;JMP" << endl;
}

void CodeWriter::writeIf(const string& label)
{
    popUnitary_();
    file_ << "@" << function_name_ << "$" << label << endl
        << "D;JNE" << endl;
}

void CodeWriter::writeFunction(const string& functionName, int numLocals)
{
    function_name_ = functionName;
    file_ << "(" << functionName << ")" << endl;
    for (int i = 0; i < numLocals; i++) {
        writePushPop(C_PUSH, "constant", 0);
    } 
}

void CodeWriter::writeReturn()
{
    file_ << "@LCL" << endl //save lcl
        << "D=M" << endl
        << "@R14" << endl
        << "M=D" << endl
        << "@5" << endl     //save ret addr
        << "A=D-A" << endl
        << "D=M" << endl
        << "@R15" << endl
        << "M=D" << endl;
    popUnitary_();          //set return value
    file_ << "@ARG" << endl
        << "A=M" << endl
        << "M=D" << endl
        << "@ARG" << endl   //set sp
        << "D=M+1" << endl
        << "@SP" << endl
        << "M=D" << endl
        << "@R14" << endl   //restore that
        << "AM=M-1" << endl
        << "D=M" << endl
        << "@THAT" << endl
        << "M=D" << endl
        << "@R14" << endl   //restore this
        << "AM=M-1" << endl
        << "D=M" << endl
        << "@THIS" << endl
        << "M=D" << endl
        << "@R14" << endl   //restore arg
        << "AM=M-1" << endl
        << "D=M" << endl
        << "@ARG" << endl
        << "M=D" << endl
        << "@R14" << endl   //restore lcl
        << "A=M-1" << endl
        << "D=M" << endl
        << "@LCL" << endl
        << "M=D" << endl
        << "@R15" << endl   //jump to ret
        << "A=M" << endl
        << "0;JMP" << endl;
}
 
void CodeWriter::writeCall(const string& functionName, int numArgs)
{
    static int return_index = 1;
    const string return_prefix  = "return_";
    file_ << "@" << return_prefix << functionName << "_" << return_index << endl
        << "D=A" << endl;
    pushStack_();
    file_ << "@LCL" << endl
        << "D=M" << endl;
    pushStack_();
    file_ << "@ARG" << endl
        << "D=M" << endl;
    pushStack_();
    file_ << "@THIS" << endl
        << "D=M" << endl;
    pushStack_();
    file_ << "@THAT" << endl
        << "D=M" << endl;
    pushStack_();
    file_ << "@SP" << endl
        << "D=M" << endl
        << "@LCL" << endl   //LCL = SP
        << "M=D" << endl
        << "@5" << endl     //ARG = SP - n - 5
        << "D=D-A" << endl
        << "@" << numArgs << endl
        << "D=D-A" << endl
        << "@ARG" << endl
        << "M=D" << endl
        << "@" << functionName << endl    //go to f 
        << "0;JMP" << endl
        << "(" << return_prefix << functionName << "_" << return_index << ")" << endl;
    return_index++;
}

void CodeWriter::close()
{
    file_.close();
}

void CodeWriter::popUnitary_()
{
    file_ << "@SP" << endl
        << "AM=M-1" << endl
        << "D=M" << endl;
}

void CodeWriter::popBinary_()
{
    popUnitary_();
    file_ << "@SP" << endl
        << "A=M-1" << endl;
}

void CodeWriter::pushStack_()
{
    file_ << "@SP" << endl
        << "A=M" << endl
        << "M=D" << endl
        << "@SP" << endl
        << "M=M+1" << endl;
}
