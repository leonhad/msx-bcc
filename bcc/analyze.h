#pragma once

#include "symbol_table.h"
#include "treenode.h"

namespace bc
{
    class Analyze
    {
        SymbolTable symtab;

      public:
        std::vector<SYMBOL_TABLE> buildSymbolTable(TreeNode *syntaxTree);

      private:
        void traverse(TreeNode *treeNode, void (Analyze::*preProc)(TreeNode *), void (Analyze::*postProc)(TreeNode *));

        void insertNode(TreeNode *treeNode);

        void nullProc(TreeNode *treeNode);
    };
}
