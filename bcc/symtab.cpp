#include "symtab.h"
#include <iostream>

using namespace std;
using namespace definitions;

namespace bc
{
    Symtab::Symtab()
    {
    }

    Symtab::~Symtab()
    {
        for (const auto &i : symtab)
        {
            delete i;
        }
    }

    void Symtab::insert(const char *name, VarType varType, ExpType expType, unsigned int lineno, unsigned int size1, unsigned int size2)
    {
        if (lookup(name, expType))
        {
            string msg;
            msg += "Var ";
            msg += name;
            msg += " already defined";
            throw msg;
        }

        SYMTAB *sym = new SYMTAB;
        sym->name = name;
        sym->varType = varType;
        sym->expType = expType;
        sym->size1 = size1;
        sym->size2 = size2;
        sym->lines.push_back(lineno);
        symtab.push_back(sym);
    }

    bool Symtab::lookup(const char *name, ExpType expType)
    {
        bool ret = false;

        for (const auto &i : symtab)
        {
            if (i->name == name && i->expType == expType)
            {
                ret = true;
            }
        }
        return ret;
    }

    vector<SYMTAB *> Symtab::getSymtab()
    {
        return symtab;
    }
} // namespace bc
