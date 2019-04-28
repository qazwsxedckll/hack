#include "code.h"

Code::Code()
{
    dest_map[""] = "000";
    dest_map["M"] = "001";
    dest_map["D"] = "010";
    dest_map["MD"] = "011";
    dest_map["A"] = "100";
    dest_map["AM"] = "101";
    dest_map["AD"] = "110";
    dest_map["AMD"] = "111";

    comp_map["0"] = "0101010";
    comp_map["1"] = "0111111";
    comp_map["-1"] = "0111010";
    comp_map["D"] = "0001100";
    comp_map["A"] = "0110000";
    comp_map["!D"] = "0001101";
    comp_map["!A"] = "0110001";
    comp_map["-D"] = "0001111";
    comp_map["-A"] = "0110011";
    comp_map["D+1"] = "0011111";
    comp_map["A+1"] = "0110111";
    comp_map["D-1"] = "0001110";
    comp_map["A-1"] = "0110010";
    comp_map["D+A"] = "0000010";
    comp_map["D-A"] = "0010011";
    comp_map["A-D"] = "0000111";
    comp_map["D&A"] = "0000000";
    comp_map["D|A"] = "0010101";
    comp_map["M"] = "1110000";
    comp_map["!M"] = "1110001";
    comp_map["-M"] = "1110011";
    comp_map["M+1"] = "1110111";
    comp_map["M-1"] = "1110010";
    comp_map["D+M"] = "1000010";
    comp_map["D-M"] = "1010011";
    comp_map["M-D"] = "1000111";
    comp_map["D&M"] = "1000000";
    comp_map["D|M"] = "1010101";

    jump_map[""] = "000";
    jump_map["JGT"] = "001";
    jump_map["JEQ"] = "010";
    jump_map["JGE"] = "011";
    jump_map["JLT"] = "100";
    jump_map["JNE"] = "101";
    jump_map["JLE"] = "110";
    jump_map["JMP"] = "111";
}

string Code::dest(const string& dest_mnemonic)
{
    if (dest_map.find(dest_mnemonic) != dest_map.end()) {
        return dest_map[dest_mnemonic];
    } else {
        cout << "Invalid syntax: code: dest" << endl;
        exit(0);
    }   
}

string Code::jump(const string& jump_mnemonic)
{
    if (jump_map.find(jump_mnemonic) != jump_map.end()) {
        return jump_map[jump_mnemonic];
    } else {
        cout << "Invalid syntax: code: jump" << endl;
        exit(0);
    }   
}

string Code::comp(const string& comp_mnemonic)
{
    if (comp_map.find(comp_mnemonic) != comp_map.end()) {
        return comp_map[comp_mnemonic];
    } else {
        cout << "Invalid syntax: code: comp" << endl;
        exit(0);
    }   
}
