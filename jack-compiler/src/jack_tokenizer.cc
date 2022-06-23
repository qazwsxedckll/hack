#include "jack_tokenizer.h"
#include <algorithm>


Jacktokenizer::Jacktokenizer(const string& s) : file_(s)
{
    if (!file_) {
        cout << "Jacktokenizer: Failed to open file" << s << endl;
        exit(1);
    }
    
    tokentype_map["class"] = TokenType::KEYWORD;
    tokentype_map["constructor"] = TokenType::KEYWORD;
    tokentype_map["function"] = TokenType::KEYWORD;
    tokentype_map["method"] = TokenType::KEYWORD;
    tokentype_map["field"] = TokenType::KEYWORD;
    tokentype_map["static"] = TokenType::KEYWORD;
    tokentype_map["var"] = TokenType::KEYWORD;
    tokentype_map["int"] = TokenType::KEYWORD;
    tokentype_map["char"] = TokenType::KEYWORD;
    tokentype_map["boolean"] = TokenType::KEYWORD;
    tokentype_map["void"] = TokenType::KEYWORD;
    tokentype_map["true"] = TokenType::KEYWORD;
    tokentype_map["false"] = TokenType::KEYWORD;
    tokentype_map["null"] = TokenType::KEYWORD;
    tokentype_map["this"] = TokenType::KEYWORD;
    tokentype_map["let"] = TokenType::KEYWORD;
    tokentype_map["do"] = TokenType::KEYWORD;
    tokentype_map["if"] = TokenType::KEYWORD;
    tokentype_map["else"] = TokenType::KEYWORD;
    tokentype_map["while"] = TokenType::KEYWORD;
    tokentype_map["return"] = TokenType::KEYWORD;
    tokentype_map["{"] = TokenType::SYMBOL;
    tokentype_map["}"] = TokenType::SYMBOL;
    tokentype_map["("] = TokenType::SYMBOL;
    tokentype_map[")"] = TokenType::SYMBOL;
    tokentype_map["["] = TokenType::SYMBOL;
    tokentype_map["]"] = TokenType::SYMBOL;
    tokentype_map["."] = TokenType::SYMBOL;
    tokentype_map[","] = TokenType::SYMBOL;
    tokentype_map[";"] = TokenType::SYMBOL;
    tokentype_map["+"] = TokenType::SYMBOL;
    tokentype_map["-"] = TokenType::SYMBOL;
    tokentype_map["*"] = TokenType::SYMBOL;
    tokentype_map["/"] = TokenType::SYMBOL;
    tokentype_map["&"] = TokenType::SYMBOL;
    tokentype_map["|"] = TokenType::SYMBOL;
    tokentype_map["<"] = TokenType::SYMBOL;
    tokentype_map[">"] = TokenType::SYMBOL;
    tokentype_map["="] = TokenType::SYMBOL;
    tokentype_map["~"] = TokenType::SYMBOL;

    keyword_map["class"] = Keyword::CLASS;
    keyword_map["constructor"] = Keyword::CONSTRUCTOR;
    keyword_map["function"] = Keyword::FUNCTION;
    keyword_map["method"] = Keyword::METHOD;
    keyword_map["field"] = Keyword::FIELD;
    keyword_map["static"] = Keyword::STATIC;
    keyword_map["var"] = Keyword::VAR;
    keyword_map["int"] = Keyword::INT;
    keyword_map["char"] = Keyword::CHAR;
    keyword_map["boolean"] = Keyword::BOOLEAN;
    keyword_map["void"] = Keyword::VOID;
    keyword_map["true"] = Keyword::K_TRUE;
    keyword_map["false"] = Keyword::K_FALSE;
    keyword_map["null"] = Keyword::K_NULL;
    keyword_map["this"] = Keyword::THIS;
    keyword_map["let"] = Keyword::LET;
    keyword_map["do"] = Keyword::DO;
    keyword_map["if"] = Keyword::IF;
    keyword_map["else"] = Keyword::ELSE;
    keyword_map["while"] = Keyword::WHILE;
    keyword_map["return"] = Keyword::RETURN;
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
            return TokenType::STRING_CONST;
        }
    }
    else if (std::all_of(current_token_.begin(), current_token_.end(), ::isdigit))
    {
        int i = std::stoi(current_token_);
        if (i >= 0 && i <= 32767)
        {
            return TokenType::INT_CONST;
        }
        else
        {
            cout << "Jacktokenizer::tokenType: Invalid int constant(" << current_token_ << ")" << endl;
            exit(1);
        }
    }
    else if (!std::isdigit(current_token_.front()))
    {
        return TokenType::IDENTIFIER;
    }
    else
    {
        cout << "Jacktokenizer::tokenType: Invalid token" << current_token_ << ")" << endl;
        exit(1);
    }
}

Keyword Jacktokenizer::keyWord()
{
    if (tokenType() == TokenType::KEYWORD)
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
    if (tokenType() == TokenType::SYMBOL)
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
    if (tokenType() == TokenType::IDENTIFIER)
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
    if (tokenType() == TokenType::INT_CONST)
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
    if (tokenType() == TokenType::STRING_CONST)
    {
        return current_token_;
    }
    else
    {
        cout << "Jacktokenizer::stringVal: Invalid token" << current_token_ << ")" << endl;
        exit(1);
    }
}

