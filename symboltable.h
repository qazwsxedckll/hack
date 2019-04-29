#ifndef __SYMBOLTABLE_H__
#define __SYMBOLTABLE_H__

#include <unordered_map>
#include <string>

using std::unordered_map;
using std::string;

class SymbolTable
{
public:
    SymbolTable();
    void AddEntry(const string& symbol, int address);
    bool contains(const string& symbol);
    int GetAddress(const string& symbol);
private:
    unordered_map<string, int> symbol_map;
};
#endif

