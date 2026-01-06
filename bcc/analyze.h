#pragma once

#include "symbol_table.h"
#include "treenode.h"

namespace bc
{
    class Analyze
    {
        SymbolTable symtab;

      public:
        std::vector<SYMBOL_TABLE> buildSymbolTable(const TreeNode *syntaxTree);

      private:
        void traverse(const TreeNode *treeNode, void (Analyze::*preProc)(const TreeNode *), void (Analyze::*postProc)(const TreeNode *));

        void insertNode(const TreeNode *treeNode);

        void nullProc(const TreeNode *treeNode);

    };
}
