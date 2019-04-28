#include <bitset>
#include "code.h"
#include "parser.h"

int main(int argc, char* argv[])
{
    string input_file, output_file;
    std::ofstream fout;

    if (argc < 2 || argc > 3) {
        cout << "Usage: " << argv[0] << " <input_file.asm> <(optional) output_file.hack>" << endl;
        exit(0);
    }
    else {
        input_file = argv[1];
        output_file = input_file.substr(0, input_file.length() - 4) + ".hack";

        if (argc == 3) {
            output_file = argv[2];
        }
    }

    fout.open(output_file);
    if (fout.fail()) {
        cout << "Failed to create output file." << endl;
        exit(0);
    }

    Parser parser(input_file);
    Code coder;
    while (parser.hasMoreCommands()) {
        parser.advance();
        if (parser.commandType() == A_COMMAND) {
            fout << "0" << std::bitset<15>(std::stoull(parser.symbol())) << endl;
        } else if (parser.commandType() == C_COMMAND) {
            fout << "111";
            fout << coder.comp(parser.comp());
            fout << coder.dest(parser.dest());
            fout << coder.jump(parser.jump());
            fout << endl;
        }
    }
    fout.close();
    return 0;
}

