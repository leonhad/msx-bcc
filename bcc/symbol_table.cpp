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

    void SymbolTable::insert(const std::string &name, const VariableType varType, const ExpressionType expression_type, const unsigned int line_number, const unsigned int size_left,
                             const unsigned int size_right)
    {
        if (lookup(name, expression_type))
        {
            string msg;
            msg += "Var ";
            msg += name;
            msg += " already defined";
            throw runtime_error(msg);
        }

        SYMBOL_TABLE sym;
        sym.name = name;
        sym.variable_type = varType;
        sym.expression_type = expression_type;
        sym.size_left = size_left;
        sym.size_right = size_right;
        sym.lines.push_back(line_number);
        table.push_back(sym);
    }

    bool SymbolTable::lookup(const std::string &name, const ExpressionType expression_type) const
    {
        bool ret = false;

        for (const auto &i : table)
        {
            if (i.name == name && i.expression_type == expression_type)
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
}
