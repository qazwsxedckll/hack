#ifndef __CODE_H__
#define __CODE_H__

#include <iostream>
#include <string>
#include <unordered_map>

using std::cout;
using std::endl;
using std::string;
using std::unordered_map;

class Code
{
public:
    Code();
    string dest(const string &dest_mnemonic);
    string jump(const string &dest_mnemonic);
    string comp(const string &dest_mnemonic);

private:
    unordered_map<string, string> dest_map;
    unordered_map<string, string> jump_map;
    unordered_map<string, string> comp_map;
};
#endif
