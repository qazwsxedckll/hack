#include "codewriter.h"
#include "parser.h"
#include <sys/types.h>
#include <dirent.h>

void ProcessFile(CodeWriter& writer, const string& file_path)
{
    Parser parser(file_path);
    string output_file = file_path.substr(0, file_path.size() - 3) + ".asm";
    writer.setFileName(output_file);
    while (parser.hasMoreCommands()) {
        parser.advance();
        CmdType cmd_type = parser.commandType();
        if (cmd_type == C_ARITHMATIC) {
            writer.writeArithmetic(parser.arg1());
        } else if (cmd_type == C_PUSH || cmd_type == C_POP) {
            writer.writePushPop(cmd_type, parser.arg1(), parser.arg2());
        }
    }
}

int main(int argc, char* argv[])
{
    string input, file_path;
    if (argc != 2) {
        cout << "Usage: " << argv[0] << " <input_file>" << endl;
        return -1;
    } else {
        input = argv[1]; 
        CodeWriter writer;
        if (input.substr(input.size() - 3, 3) == ".vm") {
            ProcessFile(writer, input);
            writer.close();
            return 0;
        } else {
            auto dir = opendir(argv[1]);
            if (dir == NULL) {
                cout << "cannot open directory: " << argv[1] << endl;
                return -1;
            }
            auto entity = readdir(dir);
            while (entity != NULL) {
                file_path = input + "/" + entity->d_name;
                if (file_path.substr(file_path.size() - 3, 3) == ".vm") {
                    ProcessFile(writer, file_path);
                }
                entity = readdir(dir);
            }
            writer.close();
            return 0;
        }
    }
}
