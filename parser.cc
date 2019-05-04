#include "parser.h"

Parser::Parser(const string& s) : file(s)
{
    if (!file.is_open()) {
        cout << "failed to open file" << s << endl;
        exit(0);
    }

    cmd_map['@'] = A_COMMAND;
    cmd_map['A'] = C_COMMAND;
    cmd_map['D'] = C_COMMAND;
    cmd_map['M'] = C_COMMAND;
    cmd_map['0'] = C_COMMAND;
    cmd_map['1'] = C_COMMAND;
    cmd_map['-'] = C_COMMAND;
    cmd_map['!'] = C_COMMAND;
    cmd_map['('] = L_COMMAND;
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
    while (!cmd_found && getline(file, current_line)) {
        //remove whitespace
        current_line.erase(remove_if(current_line.begin(), current_line.end(), ::isspace), current_line.end());

        //remvoe comment
        comment_pos = current_line.find("//");
        if (comment_pos != string::npos) {
            current_line.erase(comment_pos, current_line.size() - comment_pos);
        }
        cmd_found = !current_line.empty();
    }
    current_cmd = current_line;
}

CmdType Parser::commandType()
{
    if (cmd_map.find(current_cmd[0]) != cmd_map.end()) {
        return cmd_map[current_cmd[0]];
    }
    cout << "Invalid syntax: commandType"<< endl;
    exit(0);
}

string Parser::dest()
{
    string::size_type equal_pos;
    equal_pos = current_cmd.find("=");

    if (equal_pos != string::npos) {
        return current_cmd.substr(0, equal_pos);
    } else {
        return "";
    }
}

string Parser::comp()
{
    string::size_type equal_pos, semicolon_pos;
    equal_pos = current_cmd.find("=");
    semicolon_pos = current_cmd.find(";");

    if (equal_pos != string::npos) {
        if (semicolon_pos != string::npos) {
            // dest = comp;jmp
            return current_cmd.substr(equal_pos + 1, semicolon_pos - equal_pos - 1);
        } else {
            // dest = comp
            return current_cmd.substr(equal_pos + 1);
        }
    } else if (semicolon_pos != string::npos) {
        // comp;jmp
        return current_cmd.substr(0, semicolon_pos);
    }
    return "";
}

string Parser::jump()
{
    string::size_type semicolon_pos;
    semicolon_pos = current_cmd.find(";");

    if (semicolon_pos != string::npos) {
        return current_cmd.substr(semicolon_pos + 1);
    }
    return "";
}

string Parser::symbol()
{
    if (commandType() == A_COMMAND) {
        return current_cmd.substr(1);
    } else if (commandType() == L_COMMAND) {
        return current_cmd.substr(1, current_cmd.size() - 2);
    } else {
        cout << "Parser::symbol: not A or L command" << endl;
        exit(0);
    }
}

