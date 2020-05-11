#include "codewriter.h"
#include "parser.h"
#include <sys/types.h>
#include <dirent.h>

void ProcessFile(CodeWriter& writer, const string& file_path)
{
    Parser parser(file_path);
    writer.setFileName(file_path);
    while (parser.hasMoreCommands()) {
        parser.advance();
        CmdType cmd_type = parser.commandType();
        if (cmd_type == C_ARITHMATIC) {
            writer.writeArithmetic(parser.arg1());
        } else if (cmd_type == C_PUSH || cmd_type == C_POP) {
            writer.writePushPop(cmd_type, parser.arg1(), parser.arg2());
        } else if (cmd_type == C_LABLE) {
            writer.writeLabel(parser.arg1());
        } else if (cmd_type == C_IF) {
            writer.writeIf(parser.arg1());
        } else if (cmd_type == C_GOTO) {
            writer.writeGoto(parser.arg1());
        } else if (cmd_type == C_FUNCTION) {
            writer.writeFunction(parser.arg1(), parser.arg2());
        } else if (cmd_type == C_RETURN) {
            writer.writeReturn();
        } else if (cmd_type == C_CALL) {
            writer.writeCall(parser.arg1(), parser.arg2());
        } else {
            cout << "main::ProcessFile: Unknow command type" << endl;
            exit(1);
        }
    }
}

int main(int argc, char* argv[])
{
    string input;
    if (argc != 2) {
        cout << "Usage: " << argv[0] << " <input_file>" << endl;
        return -1;
    } else {
        input = argv[1];
        string::size_type dot_pos = input.find_last_of(".");
        if (input.substr(input.size() - 3, 3) == ".vm") {
            CodeWriter writer(input.replace(dot_pos, 3, ".asm"));
            ProcessFile(writer, argv[1]);
            writer.close();
            return 0;
        } else {
            auto dir = opendir(argv[1]);
            if (dir == NULL) {
                cout << "cannot open directory: " << argv[1] << endl;
                return -1;
            }

            if (input.back() == '/') {
                input = input.substr(0, input.length() - 1);
            }
            string output_file = input + "/" + input + ".asm";
            CodeWriter writer(output_file);
            writer.writeInit();
            auto entity = readdir(dir);
            string file_path;
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
