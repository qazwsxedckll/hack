#include "code.h"
#include "parser.h"
#include "symboltable.h"
#include <bitset>

int main(int argc, char* argv[])
{
    string input_file, output_file;
    std::ofstream fout;
    int rom_address = 0, ram_address = 16;

    if (argc < 2 || argc > 3) {
        cout << "Usage: " << argv[0] << " <input_file.asm> <(optional) output_file.hack>" << endl;
        exit(0);
    } else {
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

    Parser symbol_parser(input_file);
    Code coder;
    SymbolTable symbol_table;

    //first pass 
    while (symbol_parser.hasMoreCommands()) {
        symbol_parser.advance();
        if (symbol_parser.commandType() == C_COMMAND || symbol_parser.commandType() == A_COMMAND) {
            rom_address++;
        } else {
            symbol_table.AddEntry(symbol_parser.symbol(), rom_address);
        }
    }

    //second pass
    Parser parser(input_file);
    while (parser.hasMoreCommands()) {
        parser.advance();
        if (parser.commandType() == A_COMMAND) {
            fout << "0";
            if (parser.symbol().find_first_not_of("0123456789") != string::npos) {
                if (!symbol_table.contains(parser.symbol())) {
                    symbol_table.AddEntry(parser.symbol(), ram_address++);
                    fout << std::bitset<15>(symbol_table.GetAddress(parser.symbol()));
                } else {
                    fout << std::bitset<15>(symbol_table.GetAddress(parser.symbol()));
                }
            } else {
                fout << std::bitset<15>(stoull(parser.symbol()));
            }
            fout << endl;
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

