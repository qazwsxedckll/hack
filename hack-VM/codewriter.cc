#include "codewriter.h"

void CodeWriter::setFileName(const string& filename)
{
    if (file_) {
        file_.close();
    }
    file_.open(filename);
    string::size_type slash_pos, dot_pos;
    slash_pos = filename.find_last_of("/");
    dot_pos = filename.find_last_of(".");
    file_name_prefix_ = filename.substr(slash_pos + 1, dot_pos - slash_pos - 1);
    if (!file_) {
        cout << "Cannot open file::setFileName" << endl;
        exit(1);
    }
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
            cout << "CodeWriter:;writeArithmetic: Invalid syntax" << endl;
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
    } else {
        cout << "CodeWriter::writePushPop: Unknown command type" << endl;
        exit(1);
    }
}

void CodeWriter::writeLabel(const string& label)
{
    if (isdigit(label[0])) {
        cout << "CodeWriter::writeLable: Label starts with digit" << endl;
        exit(1);
    }
    file_ << "(L" << label << ")" << endl;
}

void CodeWriter::writeGoto(const string& label)
{
    file_ << "@L" << label << endl
        << "0;JMP" << endl;
}

void CodeWriter::writeIf(const string& label)
{
    popUnitary_();
    file_ << "@L" << label << endl
        << "D;JNE" << endl;
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
    file_ << "@SP" << endl
        << "AM=M-1" << endl
        << "D=M" << endl
        << "@SP" << endl
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

