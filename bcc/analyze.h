#pragma once

#include "symbol_table.h"
#include "treenode.h"

namespace bc
{
    class Analyze
    {
        SymbolTable symtab;

        void traverse(const TreeNode *treeNode, void (Analyze::*preProc)(const TreeNode *), void (Analyze::*postProc)(const TreeNode *));

        void insertNode(const TreeNode *treeNode);

        void nullProc(const TreeNode *treeNode);

      public:
        std::vector<SYMBOL_TABLE> buildSymbolTable(const TreeNode *syntaxTree);
    };
}
