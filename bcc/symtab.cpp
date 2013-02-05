#include "symtab.h"
#include <iostream>

namespace bc
{
    Symtab::Symtab()
    {
        
    }
    Symtab::~Symtab()
    {
        vector<SYMTAB *>::iterator i;
        for (i = symtab.begin(); i != symtab.end(); i++) {
            delete (*i);
        }
    }
    
    void Symtab::insert(const char * name, VarType varType, ExpType expType, unsigned int lineno, unsigned int size1, unsigned int size2)
    {
        if (lookup(name, expType)) {
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
    
    bool Symtab::lookup(const char * name, ExpType expType)
    {
        register bool ret = false;
        vector<SYMTAB *>::iterator i;
        for (i = symtab.begin(); i != symtab.end(); i++) {
            if ((*i)->name == name && (*i)->expType == expType) {
                ret = true;
            }
        }
        return ret;
    }
    
    vector<SYMTAB *> Symtab::getSymtab()
    {
        return symtab;
    }
}
