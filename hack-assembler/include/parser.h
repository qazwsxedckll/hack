#ifndef __PARSER_H__
#define __PARSER_H__

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <unordered_map>

using std::endl;
using std::cin;
using std::cout;
using std::string;
using std::unordered_map;

enum CmdType { A_COMMAND, C_COMMAND, L_COMMAND };

class Parser
{
public:
    Parser(const string& s);
    //Opens the input file/stream and gets ready to parse it
    bool hasMoreCommands();
    //Are there more commands in the input?
    void advance();
    //Reads the next command from the input and makes it the current command
    CmdType commandType();
    //return the type of currend command
    string symbol();
    //Returns the symbol or decimal Xxx of the current command @Xxx or (Xxx).
    string dest();
    //Returns the dest mnemonic in the current C-command. 
    string comp();
    //Returns the comp mnemonic in the current C-command.
    string jump();
    //Returns the jump mnemonic in the current C-command.
private:
    std::ifstream file;
    string current_cmd;
    unordered_map<char, CmdType> cmd_map;
};
#endif

