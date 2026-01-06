#include "symbol_table.h"
#include <iostream>
#include <stdexcept>

using namespace std;
using namespace definitions;

namespace bc
{
    SymbolTable::SymbolTable()
    {
        location = 0;
    }

    void SymbolTable::insert(const char *name, VarType varType, ExpType expType, unsigned int lineno, unsigned int size1, unsigned int size2)
    {
        if (lookup(name, expType))
        {
            string msg;
            msg += "Var ";
            msg += name;
            msg += " already defined";
            throw runtime_error(msg);
        }

        SYMBOL_TABLE sym;
        sym.name = name;
        sym.varType = varType;
        sym.expType = expType;
        sym.size1 = size1;
        sym.size2 = size2;
        sym.lines.push_back(lineno);
        symtab.push_back(sym);
    }

    bool SymbolTable::lookup(const char *name, const ExpType expType)
    {
        bool ret = false;

        for (const auto &i : symtab)
        {
            if (i.name == name && i.expType == expType)
            {
                ret = true;
            }
        }
        return ret;
    }

    vector<SYMBOL_TABLE> SymbolTable::getSymtab()
    {
        return symtab;
    }
} // namespace bc
