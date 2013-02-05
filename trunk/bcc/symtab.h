//
// File:   symtab.h
// Author: p922221
//
// Created on 2 de Abril de 2008, 15:01
//

#ifndef _SYMTAB_H
#define	_SYMTAB_H

#include "attributes.h"
#include <vector>
#include <string>

using namespace definitions;
using namespace std;

namespace bc
{
    enum VarType {
        DimV,
        VarV
    };
    
    typedef struct
    {
        string name;
        VarType varType;
        ExpType expType;
        vector<unsigned int> lines;
        unsigned int memloc;
        unsigned int size1;
        unsigned int size2;
    } SYMTAB;
    
    class Symtab
    {
    private:
        unsigned int location;
        vector<SYMTAB *> symtab;
        
    public:
        Symtab();
        ~Symtab();
        
        void insert(const char * name, VarType varType, ExpType expType, unsigned int lineno, unsigned int size1 = 0, unsigned int size2 = 0);
        bool lookup(const char * name, ExpType expType);
        
        vector<SYMTAB *> getSymtab();
    };
}

#endif	/* _SYMTAB_H */

