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
        const std::filesystem::path output(input.relative_path().replace_extension("T.xml"));
        CompilationEngine engine(input, output);
        cout << "<tokens>" << endl;
        while (tokenizer.hasMoreTokens())
        {
            tokenizer.advance();
            auto type = tokenizer.tokenType();
            switch (type)
            {
            case TokenType::KEYWORD:
            {
                cout << "<keyword> ";
                auto keyword = tokenizer.keyWord();
                switch (keyword)
                {
                case Keyword::CLASS:
                    cout << "class";
                    break;
                case Keyword::METHOD:
                    cout << "method";
                    break;
                case Keyword::FUNCTION:
                    cout << "function";
                    break;
                case Keyword::CONSTRUCTOR:
                    cout << "constructor";
                    break;
                case Keyword::INT:
                    cout << "int";
                    break;
                case Keyword::BOOLEAN:
                    cout << "boolean";
                    break;
                case Keyword::CHAR:
                    cout << "char";
                    break;
                case Keyword::VOID:
                    cout << "void";
                    break;
                case Keyword::VAR:
                    cout << "var";
                    break;
                case Keyword::STATIC:
                    cout << "static";
                    break;
                case Keyword::FIELD:
                    cout << "field";
                    break;
                case Keyword::LET:
                    cout << "let";
                    break;
                case Keyword::DO:
                    cout << "do";
                    break;
                case Keyword::IF:
                    cout << "if";
                    break;
                case Keyword::ELSE:
                    cout << "else";
                    break;
                case Keyword::WHILE:
                    cout << "while";
                    break;
                case Keyword::RETURN:
                    cout << "return";
                    break;
                case Keyword::K_TRUE:
                    cout << "true";
                    break;
                case Keyword::K_FALSE:
                    cout << "false";
                    break;
                case Keyword::K_NULL:
                    cout << "null";
                    break;
                case Keyword::THIS:
                    cout << "this";
                    break;
                default:
                    cout << "Unknown keyword(" << int(keyword) << ")" << endl;
                    exit(1);
                    break;
                }
                cout << " </keyword>" << endl;
                break;
            }
            case TokenType::SYMBOL:
                cout << "<symbol> " << tokenizer.symbol() << " </symbol>" << endl;
                break;
            case TokenType::IDENTIFIER:
                cout << "<identifier> " << tokenizer.identifier() << " </identifier>" << endl;
                break;
            case TokenType::INT_CONST:
                cout << "<integerConstant> " << tokenizer.intVal() << " </integerConstant>" << endl;
                break;
            case TokenType::STRING_CONST:
                cout << "<stringConstant> " << tokenizer.stringVal() << " </stringConstant>" << endl;
                break;
            default:
                cout << "Unknown token type(" << int(type) << ")" << endl;
                exit(1);
                break;
            }
        }
        cout << "</tokens>" << endl;
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