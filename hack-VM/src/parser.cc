#include "parser.h"

Parser::Parser(const string& s) : file(s)
{
    if (!file.is_open()) {
        cout << "Failed to open file: Parser" << endl;
        exit(1);
    }

    cmd_map["add"] = C_ARITHMATIC;
    cmd_map["sub"] = C_ARITHMATIC;
    cmd_map["neg"] = C_ARITHMATIC;
    cmd_map["eq"] = C_ARITHMATIC;
    cmd_map["gt"] = C_ARITHMATIC;
    cmd_map["lt"] = C_ARITHMATIC;
    cmd_map["and"] = C_ARITHMATIC;
    cmd_map["or"] = C_ARITHMATIC;
    cmd_map["not"] = C_ARITHMATIC;
    cmd_map["push"] = C_PUSH;
    cmd_map["pop"] = C_POP;
    cmd_map["label"] = C_LABLE;
    cmd_map["if-goto"] = C_IF;
    cmd_map["goto"] = C_GOTO;
    cmd_map["function"] = C_FUNCTION;
    cmd_map["return"] = C_RETURN;
    cmd_map["call"] = C_CALL;
}

bool Parser::hasMoreCommands()
{
    return (file.peek() != EOF);
}

void Parser::advance()
{
    string current_line;
    bool cmd_found = false;
    string::size_type comment_pos;
    string::size_type end_pos;
    while (!cmd_found && getline(file, current_line)) {
        //remove \n
        current_line.pop_back();

        //remove comment
        comment_pos = current_line.find("//");
        if (comment_pos != string::npos) {
            current_line.erase(comment_pos, current_line.size() - comment_pos);
        }

        end_pos = current_line.find_last_not_of(" ");
        current_line = current_line.substr(0, end_pos + 1);

        cmd_found = !current_line.empty();
    }
    current_cmd = current_line;
}

CmdType Parser::commandType()
{
    string::size_type space_pos = current_cmd.find_first_of(" \n");
    string prefix = current_cmd.substr(0, space_pos);
    if (cmd_map.find(prefix) != cmd_map.end()) {
        return cmd_map[prefix];
    }
    cout << "Parser::commandType: Invalid syntax" << endl;
    exit(1);
}

string Parser::arg1()
{
    if (commandType() == C_ARITHMATIC) {
        return current_cmd;
    } else if (commandType() == C_RETURN) {
        cout << "Parser::arg1: Invalid syntax: Called with C_RETURN" << endl;
        exit(1);
    } else {
        string::size_type first_space = current_cmd.find_first_of(" ");
        string::size_type second_space = current_cmd.find_first_of(" \n", first_space + 1);
        return current_cmd.substr(first_space + 1, second_space - first_space - 1);
    }
}

int Parser::arg2()
{
    string::size_type end_pos = current_cmd.find_last_not_of(" ");
    string::size_type space_pos = current_cmd.find_last_of(" ", end_pos);
    return stoi(current_cmd.substr(space_pos + 1, end_pos - space_pos));
}

