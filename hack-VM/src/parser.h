#ifndef __PARSER_H__
#define __PARSER_H__

#include <fstream>
#include <string>
#include <iostream>
#include <unordered_map>

using std::string;
using std::ifstream;
using std::cout;
using std::endl;
using std::unordered_map;

enum CmdType { C_ARITHMATIC, C_PUSH, C_POP, C_LABLE, C_GOTO,
        C_IF, C_FUNCTION, C_RETURN, C_CALL };

class Parser
{
public:
    Parser(const string& s);
    bool hasMoreCommands();
    void advance();
    CmdType commandType();
    string arg1();
    int arg2();
    ~Parser() {}
private:
    ifstream file;
    unordered_map<string, CmdType> cmd_map;
    string current_cmd;
};
#endif
