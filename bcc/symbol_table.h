#ifndef SYMTAB_H
#define SYMTAB_H

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
    } SYMBOL_TABLE;

    class SymbolTable
    {
        unsigned int location;
        std::vector<SYMBOL_TABLE> symtab;

      public:
        SymbolTable();
        void insert(const char *name, VarType varType, definitions::ExpType expType, unsigned int lineno, unsigned int size1 = 0, unsigned int size2 = 0);
        bool lookup(const char *name, definitions::ExpType expType);

        std::vector<SYMBOL_TABLE> getSymtab();
    };
} // namespace bc

#endif /* SYMTAB_H */
