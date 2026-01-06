#pragma once

#include "symbol_table.h"
#include "treenode.h"

namespace bc
{
    class Analyze
    {
        SymbolTable symbols;

        void traverse(const TreeNode *tree_node, void (Analyze::*pre_proc)(const TreeNode *), void (Analyze::*post_proc)(const TreeNode *));

        void insert_node(const TreeNode *tree_node);

        void nullProc(const TreeNode *tree_node);

      public:
        std::vector<SYMBOL_TABLE> buildSymbolTable(const TreeNode *syntax_tree);
    };
}
