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
        unsigned int size1;
        unsigned int size2;
    } SYMBOL_TABLE;

    class SymbolTable
    {
        unsigned int location;
        std::vector<SYMBOL_TABLE> table;

      public:
        SymbolTable();
        void insert(const std::string &name, VarType varType, definitions::ExpType expType, unsigned int lineno, unsigned int size1 = 0, unsigned int size2 = 0);
        [[nodiscard]] bool lookup(const std::string &name, definitions::ExpType expType) const;

        std::vector<SYMBOL_TABLE> get();
    };
} // namespace bc

#endif /* SYMTAB_H */
