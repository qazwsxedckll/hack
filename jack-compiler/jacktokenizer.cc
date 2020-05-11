#include "jacktokenizer.h"
#include <algorithm>


Jacktokenizer::Jacktokenizer(const string& s) : file_(s)
{
    if (!file_) {
        cout << "Jacktokenizer: Failed to open file" << s << endl;
        exit(1);
    }
    
    tokentype_map["class"] = KEYWORD;
    tokentype_map["constructor"] = KEYWORD;
    tokentype_map["function"] = KEYWORD;
    tokentype_map["method"] = KEYWORD;
    tokentype_map["field"] = KEYWORD;
    tokentype_map["static"] = KEYWORD;
    tokentype_map["var"] = KEYWORD;
    tokentype_map["int"] = KEYWORD;
    tokentype_map["char"] = KEYWORD;
    tokentype_map["boolean"] = KEYWORD;
    tokentype_map["void"] = KEYWORD;
    tokentype_map["true"] = KEYWORD;
    tokentype_map["false"] = KEYWORD;
    tokentype_map["null"] = KEYWORD;
    tokentype_map["this"] = KEYWORD;
    tokentype_map["let"] = KEYWORD;
    tokentype_map["do"] = KEYWORD;
    tokentype_map["if"] = KEYWORD;
    tokentype_map["else"] = KEYWORD;
    tokentype_map["while"] = KEYWORD;
    tokentype_map["return"] = KEYWORD;
    tokentype_map["{"] = SYMBOL;
    tokentype_map["}"] = SYMBOL;
    tokentype_map["("] = SYMBOL;
    tokentype_map[")"] = SYMBOL;
    tokentype_map["["] = SYMBOL;
    tokentype_map["]"] = SYMBOL;
    tokentype_map["."] = SYMBOL;
    tokentype_map[","] = SYMBOL;
    tokentype_map[";"] = SYMBOL;
    tokentype_map["+"] = SYMBOL;
    tokentype_map["-"] = SYMBOL;
    tokentype_map["*"] = SYMBOL;
    tokentype_map["/"] = SYMBOL;
    tokentype_map["&"] = SYMBOL;
    tokentype_map["|"] = SYMBOL;
    tokentype_map["<"] = SYMBOL;
    tokentype_map[">"] = SYMBOL;
    tokentype_map["="] = SYMBOL;
    tokentype_map["~"] = SYMBOL;

    keyword_map["class"] = CLASS;
    keyword_map["constructor"] = CONSTRUCTOR;
    keyword_map["function"] = FUNCTION;
    keyword_map["method"] = METHOD;
    keyword_map["field"] = FIELD;
    keyword_map["static"] = STATIC;
    keyword_map["var"] = VAR;
    keyword_map["int"] = INT;
    keyword_map["char"] = CHAR;
    keyword_map["boolean"] = BOOLEAN;
    keyword_map["void"] = VOID;
    keyword_map["true"] = K_TRUE;
    keyword_map["false"] = K_FALSE;
    keyword_map["null"] = K_NULL;
    keyword_map["this"] = THIS;
    keyword_map["let"] = LET;
    keyword_map["do"] = DO;
    keyword_map["if"] = IF;
    keyword_map["else"] = ELSE;
    keyword_map["while"] = WHILE;
    keyword_map["return"] = RETURN;
}

bool Jacktokenizer::hasMoreTokens()
{
    return (file_.peek() != EOF || line_stream_);
}

void Jacktokenizer::advance()
{
    if (line_stream_) {
        line_stream_ >> current_token_;
        //test
        cout << "current_token_: " << current_token_ << endl;
        return;
    }

    string current_line;
    bool token_found = false;
    bool comment_found = false;
    string::size_type comment_start, comment_end;
    while (!token_found && getline(file_, current_line)) {
        // inside comment
        if (comment_found == true) {
            comment_end = current_line.find("*/");
            if (comment_end == string::npos) {
                continue;
            }
            else {
                comment_found = false;
                current_line.erase(0, comment_end + 2);
            }
        }

        //remove /* comments
        comment_start = current_line.find("/*");
        if (comment_start != string::npos) {
            comment_found = true;
            comment_end = current_line.find("*/");
            if (comment_end != string::npos) {
                comment_found = false;
                current_line.erase(comment_start, comment_end - comment_start + 2);
            }
        }

        //remove //comment
        comment_start = current_line.find("//");
        if (comment_start != string::npos)
        {
            current_line.erase(comment_start);
        }

        //remove \n
        current_line.pop_back();
        if (current_line.empty()) {
            continue;
        }
    }
}

TokenType Jacktokenizer::tokenType()
{
    //keyword & symbol
    if (tokentype_map.find(current_token_) != tokentype_map.end())
    {
        return tokentype_map[current_token_];
    }
    // string constant
    else if (current_token_.front() == '"' && current_token_.back() == '"')
    {
        if (current_token_.find("\n", 1) != string::npos
            ||current_token_.find("\"", 1, current_token_.length() - 2))
        {
            cout << "Jacktokenizer::tokenType: Invalid string constant(" << current_token_ << ")" << endl;
            exit(1);
        }
        else
        {
            return STRING_CONST;
        }
    }
    else if (std::all_of(current_token_.begin(), current_token_.end(), ::isdigit))
    {
        int i = std::stoi(current_token_);
        if (i >= 0 && i <= 32767)
        {
            return INT_CONST;
        }
        else
        {
            cout << "Jacktokenizer::tokenType: Invalid int constant(" << current_token_ << ")" << endl;
            exit(1);
        }
    }
    else if (!std::isdigit(current_token_.front()))
    {
        return IDENTIFIER;
    }
    else
    {
        cout << "Jacktokenizer::tokenType: Invalid token" << current_token_ << ")" << endl;
        exit(1);
    }
}

Keyword Jacktokenizer::keyWord()
{
    if (tokenType() == KEYWORD)
    {
        return keyword_map[current_token_];
    }
    else
    {
        cout << "Jacktokenizer::keyWord: Invalid token" << current_token_ << ")" << endl;
        exit(1);
    }
}

char Jacktokenizer::symbol()
{
    if (tokenType() == SYMBOL)
    {
        return current_token_.front();
    }
    else
    {
        cout << "Jacktokenizer::symbol: Invalid token" << current_token_ << ")" << endl;
        exit(1);
    }
}

string Jacktokenizer::identifier()
{
    if (tokenType() == IDENTIFIER)
    {
        return current_token_;
    }
    else
    {
        cout << "Jacktokenizer::identifier: Invalid token" << current_token_ << ")" << endl;
        exit(1);
    }
}

int Jacktokenizer::intVal()
{
    if (tokenType() == INT_CONST)
    {
        return std::stoi(current_token_);
    }
    else
    {
        cout << "Jacktokenizer::intVal: Invalid token" << current_token_ << ")" << endl;
        exit(1);
    }
}

string Jacktokenizer::stringVal()
{
    if (tokenType() == STRING_CONST)
    {
        return current_token_;
    }
    else
    {
        cout << "Jacktokenizer::stringVal: Invalid token" << current_token_ << ")" << endl;
        exit(1);
    }
}

