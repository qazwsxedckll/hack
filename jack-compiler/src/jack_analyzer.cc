#include "jack_analyzer.h"
#include "jack_tokenizer.h"
#include "compilation_engine.h"

#include <filesystem>

using namespace std;

bool IsJackFile(const string& file_name)
{
    auto dot_pos = file_name.find_last_of(".");
    if (dot_pos == string::npos)
    {
        return false;
    }

    if (file_name.substr(dot_pos) == ".jack")
    {
        return true;
    }

    return false;
}

int Analyze(const string& file_name)
{
    const std::filesystem::path input(file_name);
    if (IsJackFile(input))
    {
        Jacktokenizer tokenizer(input);

        const std::filesystem::path output(input.relative_path().replace_extension(".xml"));
        CompilationEngine engine(input, output);

        const std::filesystem::path tmpout(input.relative_path().replace_filename(output.stem().concat("T.xml")));
        std::ofstream tmp_out_file(tmpout);

        if (!tmp_out_file)
        {
            cout << "Jacktokenizer: Failed to open file(" << tmpout << ")" << endl;
            exit(1);
        }

        tmp_out_file << "<tokens>" << endl;
        while (tokenizer.hasMoreTokens())
        {
            tokenizer.advance();
            auto type = tokenizer.tokenType();
            switch (type)
            {
            case TokenType::KEYWORD:
            {
                tmp_out_file << "<keyword> ";
                auto keyword = tokenizer.keyWord();
                switch (keyword)
                {
                case Keyword::CLASS:
                    tmp_out_file << "class";
                    break;
                case Keyword::METHOD:
                    tmp_out_file << "method";
                    break;
                case Keyword::FUNCTION:
                    tmp_out_file << "function";
                    break;
                case Keyword::CONSTRUCTOR:
                    tmp_out_file << "constructor";
                    break;
                case Keyword::INT:
                    tmp_out_file << "int";
                    break;
                case Keyword::BOOLEAN:
                    tmp_out_file << "boolean";
                    break;
                case Keyword::CHAR:
                    tmp_out_file << "char";
                    break;
                case Keyword::VOID:
                    tmp_out_file << "void";
                    break;
                case Keyword::VAR:
                    tmp_out_file << "var";
                    break;
                case Keyword::STATIC:
                    tmp_out_file << "static";
                    break;
                case Keyword::FIELD:
                    tmp_out_file << "field";
                    break;
                case Keyword::LET:
                    tmp_out_file << "let";
                    break;
                case Keyword::DO:
                    tmp_out_file << "do";
                    break;
                case Keyword::IF:
                    tmp_out_file << "if";
                    break;
                case Keyword::ELSE:
                    tmp_out_file << "else";
                    break;
                case Keyword::WHILE:
                    tmp_out_file << "while";
                    break;
                case Keyword::RETURN:
                    tmp_out_file << "return";
                    break;
                case Keyword::K_TRUE:
                    tmp_out_file << "true";
                    break;
                case Keyword::K_FALSE:
                    tmp_out_file << "false";
                    break;
                case Keyword::K_NULL:
                    tmp_out_file << "null";
                    break;
                case Keyword::THIS:
                    tmp_out_file << "this";
                    break;
                default:
                    cout << "Unknown keyword(" << int(keyword) << ")" << endl;
                    exit(1);
                    break;
                }
                tmp_out_file << " </keyword>" << endl;
                break;
            }
            case TokenType::SYMBOL:
            {
                tmp_out_file << "<symbol> ";
                auto symbol = tokenizer.symbol();
                if (symbol == '<') {
                    tmp_out_file << "&lt;";
                } else if (symbol == '>') {
                    tmp_out_file << "&gt;";
                } else if (symbol == '"') {
                    tmp_out_file << "&quot;";
                } else if (symbol == '&') {
                    tmp_out_file << "&amp;";
                } else {
                    tmp_out_file << symbol;
                }
                tmp_out_file << " </symbol>" << endl;
                break;
            }
            case TokenType::IDENTIFIER:
                tmp_out_file << "<identifier> " << tokenizer.identifier() << " </identifier>" << endl;
                break;
            case TokenType::INT_CONST:
                tmp_out_file << "<integerConstant> " << tokenizer.intVal() << " </integerConstant>" << endl;
                break;
            case TokenType::STRING_CONST:
                tmp_out_file << "<stringConstant> " << tokenizer.stringVal() << " </stringConstant>" << endl;
                break;
            default:
                cout << "Unknown token type(" << int(type) << ")" << endl;
                exit(1);
                break;
            }
        }
        tmp_out_file << "</tokens>" << endl;
        tmp_out_file.close();
    }
    else
    {
        // auto dir = opendir(argv[1]);
        // if (dir == NULL) {
        //     cout << "cannot open directory: " << argv[1] << endl;
        //     return -1;
        // }

        // if (input.back() == '/') {
        //     input = input.substr(0, input.length() - 1);
        // }
        // auto entity = readdir(dir);
        // string file_path;
        // while (entity != NULL) {
        //     file_path = input + "/" + entity->d_name;
        //     if (IsJackFile(file_path)) {
        //     }
        //     entity = readdir(dir);
        // }
    }

    return 0;
}