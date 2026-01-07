#pragma once

#include "attributes.h"
#include <string>
#include <vector>

namespace bc
{
    enum VariableType
    {
        DIM_V,
        VARIABLE_V
    };

    typedef struct
    {
        std::string name;
        VariableType variable_type;
        ExpressionType expression_type;
        std::vector<unsigned int> lines;
        unsigned int size_left;
        unsigned int size_right;
    } SYMBOL_TABLE;

    class SymbolTable
    {
        unsigned int location;
        std::vector<SYMBOL_TABLE> table;

      public:
        SymbolTable();
        void insert(const std::string &name, VariableType varType, ExpressionType expression_type, unsigned int line_number, unsigned int size_left = 0, unsigned int size_right = 0);
        [[nodiscard]] bool lookup(const std::string &name, ExpressionType expression_type) const;

        std::vector<SYMBOL_TABLE> get();
    };
}
