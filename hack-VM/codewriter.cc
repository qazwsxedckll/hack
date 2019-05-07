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
        file_ << "@SP" << endl
            << "AM=M-1" << endl
            << "D=M" << endl
            << "@SP" << endl
            << "A=M-1" << endl
            << "M=D+M" << endl;
    }
    if (command.compare("sub") == 0) {
        file_ << "@SP" << endl
            << "AM=M-1" << endl
            << "D=M" << endl
            << "@SP" << endl
            << "A=M-1" << endl
            << "M=M-D" << endl;
    }
    if (command.compare("neg") == 0) {
        file_ << "@SP" << endl
            << "A=M-1" << endl
            << "M=-M" << endl;
    }
    if (command.compare("and") == 0) {
        file_ << "@SP" << endl
            << "AM=M-1" << endl
            << "D=M" << endl
            << "@SP" << endl
            << "A=M-1" << endl
            << "M=D&M" << endl;
    }
    if (command.compare("or") == 0) {
        file_ << "@SP" << endl
            << "AM=M-1" << endl
            << "D=M" << endl
            << "@SP" << endl
            << "A=M-1" << endl
            << "M=D|M" << endl;
    }
    if (command.compare("not") == 0) {
        file_ << "@SP" << endl
            << "A=M-1" << endl
            << "M=!M" << endl;
    }

    static int eq = 1;
    if (command.compare("eq") == 0) {
        file_ << "@SP" << endl
            << "AM=M-1" << endl
            << "D=M" << endl
            << "@SP" << endl
            << "A=M-1" << endl
            << "D=D-M" << endl
            << "@EQ" << eq << endl
            << "D;JEQ" << endl
            << "@SP" << endl
            << "A=M-1" << endl
            << "M=0" << endl
            << "@EQEND" << eq << endl
            << "0;JMP" << endl
            << "(EQ" << eq << ")" << endl
            << "@SP" << endl
            << "A=M-1" << endl
            << "M=-1" << endl
            << "(EQEND" << eq << ")" << endl;
        eq++;
    }

    static int gt = 1;
    if (command.compare("gt") == 0) {
        file_ << "@SP" << endl
            << "AM=M-1" << endl
            << "D=M" << endl
            << "@SP" << endl
            << "A=M-1" << endl
            << "D=D-M" << endl
            << "@GT" << gt << endl
            << "D;JLT" << endl
            << "@SP" << endl
            << "A=M-1" << endl
            << "M=0" << endl
            << "@GTEND" << gt << endl
            << "0;JMP" << endl
            << "(GT" << gt << ")" << endl
            << "@SP" << endl
            << "A=M-1" << endl
            << "M=-1" << endl
            << "(GTEND" << gt << ")" << endl;
        gt++;
    }

    static int lt = 1;
    if (command.compare("lt") == 0) {
        file_ << "@SP" << endl
            << "AM=M-1" << endl
            << "D=M" << endl
            << "@SP" << endl
            << "A=M-1" << endl
            << "D=D-M" << endl
            << "@LT" << lt << endl
            << "D;JGT" << endl
            << "@SP" << endl
            << "A=M-1" << endl
            << "M=0" << endl
            << "@LTEND" << lt << endl
            << "0;JMP" << endl
            << "(LT" << lt << ")" << endl
            << "@SP" << endl
            << "A=M-1" << endl
            << "M=-1" << endl
            << "(LTEND" << lt << ")" << endl;
        lt++;
    }
}

void CodeWriter::writePushPop(const CmdType& command, const string& segment, int index)
{
    if (command == C_PUSH) {
        if (segment.compare("constant") == 0){
            file_ << "@" << index << endl
                << "D=A" << endl
                << "@SP" <<  endl
                << "A=M" << endl
                << "M=D" <<  endl
                << "@SP" << endl
                << "M=M+1" << endl;
            return;
        }
        if (segment.compare("static") == 0) {
            file_ << "@" << file_name_prefix_ << "." << index << endl
                << "D=M" << endl
                << "@SP" <<  endl
                << "A=M" << endl
                << "M=D" <<  endl
                << "@SP" << endl
                << "M=M+1" << endl;
            return;
        }

        if (segment.compare("local") == 0) {
            file_ << "@LCL" << endl
                << "D=M" << endl;
        }
        if (segment.compare("argument") == 0) {
            file_ << "@ARG" << endl
                << "D=M" << endl;
        }
        if (segment.compare("this") == 0) {
            file_ << "@THIS" << endl
                << "D=M" << endl;
        }
        if (segment.compare("that") == 0) {
            file_ << "@THAT" << endl
                << "D=M" << endl;
        }
        if (segment.compare("temp") == 0) {
            file_ << "@R5" << endl
                << "D=A" << endl;
        }
        if (segment.compare("pointer") == 0) {
            file_ << "@R3" << endl
                << "D=A" << endl;
        }
        //pushstack
        file_ << "@" << index << endl
            << "A=D+A" << endl
            << "D=M" << endl
            << "@SP" <<  endl
            << "A=M" << endl
            << "M=D" <<  endl
            << "@SP" << endl
            << "M=M+1" << endl;
    }

    if (command == C_POP) {
        file_ << "@SP" << endl
            << "AM=M-1" << endl
            << "D=M" << endl
            << "@R14" << endl
            << "M=D" << endl;
        if (segment.compare("local") == 0) {
            file_ << "@LCL" << endl
                << "D=M" << endl;
        }
        if (segment.compare("argument") == 0) {
            file_ << "@ARG" << endl
                << "D=M" << endl;
        }
        if (segment.compare("this") == 0) {
            file_ << "@THIS" << endl
                << "D=M" << endl;
        }
        if (segment.compare("that") == 0) {
            file_ << "@THAT" << endl
                << "D=M" << endl;
        }
        if (segment.compare("temp") == 0) {
            file_ << "@R5" << endl
                << "D=A" << endl;
        }
        if (segment.compare("pointer") == 0) {
            file_ << "@R3" << endl
                << "D=A" << endl;
        }
        if (segment.compare("static") == 0) {
            file_ << "@" << file_name_prefix_ << "." << index << endl
                << "D=A" << endl
                << "@R15" << endl
                << "M=D" << endl
                << "@R14" << endl
                << "D=M" << endl
                << "@R15" << endl
                << "A=M" << endl
                << "M=D" << endl;
            return;
        }
        file_ << "@" << index << endl
            << "D=D+A" << endl
            << "@R15" << endl
            << "M=D" << endl
            << "@R14" << endl
            << "D=M" << endl
            << "@R15" << endl
            << "A=M" << endl
            << "M=D" << endl;
    }
}

void CodeWriter::close()
{
    file_.close();
}

