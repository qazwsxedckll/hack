#include "symboltable.h"

SymbolTable::SymbolTable()
{
    symbol_map["SP"] = 0;
    symbol_map["LCL"] = 1;
    symbol_map["ARG"] = 2;
    symbol_map["THIS"] = 3;
    symbol_map["THAT"] = 4;
    symbol_map["R0"] = 0;
    symbol_map["R1"] = 1;
    symbol_map["R2"] = 2;
    symbol_map["R3"] = 3;
    symbol_map["R4"] = 4;
    symbol_map["R5"] = 5;
    symbol_map["R6"] = 6;
    symbol_map["R7"] = 7;
    symbol_map["R8"] = 8;
    symbol_map["R9"] = 9;
    symbol_map["R10"] = 10;
    symbol_map["R11"] = 11;
    symbol_map["R12"] = 12;
    symbol_map["R13"] = 13;
    symbol_map["R14"] = 14;
    symbol_map["R15"] = 15;
    symbol_map["SCREEN"] = 16384;
    symbol_map["KBD"] = 24576;
}

void SymbolTable::AddEntry(const string &symbol, int address)
{
    if (symbol_map.find(symbol) == symbol_map.end())
    {
        symbol_map[symbol] = address;
    }
}

bool SymbolTable::contains(const string &symbol)
{
    return (symbol_map.find(symbol) != symbol_map.end());
}

int SymbolTable::GetAddress(const string &symbol)
{
    if (symbol_map.find(symbol) != symbol_map.end())
    {
        return symbol_map[symbol];
    }
    else
    {
        return 0;
    }
}
