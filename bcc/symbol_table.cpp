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

    void SymbolTable::insert(const std::string &name, const VarType varType, const ExpType expType, const unsigned int lineno, const unsigned int size1, const unsigned int size2)
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
        table.push_back(sym);
    }

    bool SymbolTable::lookup(const std::string &name, const ExpType expType) const
    {
        bool ret = false;

        for (const auto &i : table)
        {
            if (i.name == name && i.expType == expType)
            {
                ret = true;
            }
        }

        return ret;
    }

    vector<SYMBOL_TABLE> SymbolTable::get()
    {
        return table;
    }
} // namespace bc
