#ifndef __SYMBOLTABLE_H__
#define __SYMBOLTABLE_H__

#include <string>
#include <unordered_map>

using std::string;
using std::unordered_map;

class SymbolTable
{
public:
    SymbolTable();
    void AddEntry(const string &symbol, int address);
    bool contains(const string &symbol);
    int GetAddress(const string &symbol);

private:
    unordered_map<string, int> symbol_map;
};
#endif
