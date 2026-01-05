//
// File:   symtab.h
// Author: p922221
//
// Created on 2 de Abril de 2008, 15:01
//

#ifndef _SYMTAB_H
#define _SYMTAB_H

#include <string>
#include <vector>

#include "attributes.h"

namespace bc
{
    enum VarType
    {
        DimV,
        VarV
    };

    typedef struct
    {
        std::string name;
        VarType varType;
        definitions::ExpType expType;
        std::vector<unsigned int> lines;
        unsigned int memloc;
        unsigned int size1;
        unsigned int size2;
    } SYMTAB;

    class Symtab
    {
        unsigned int location;
        std::vector<SYMTAB *> symtab;

      public:
        Symtab();
        ~Symtab();

        void insert(const char *name, VarType varType, definitions::ExpType expType, unsigned int lineno, unsigned int size1 = 0, unsigned int size2 = 0);
        bool lookup(const char *name, definitions::ExpType expType);

        std::vector<SYMTAB *> getSymtab();
    };
} // namespace bc

#endif /* _SYMTAB_H */
