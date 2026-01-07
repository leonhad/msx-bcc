#include "analyze.h"
#include "numbers.h"
#include "treenode.h"

namespace bc
{
    std::vector<SYMBOL_TABLE> Analyze::buildSymbolTable(const TreeNode *syntax_tree)
    {
        traverse(syntax_tree, &Analyze::insert_node, &Analyze::nullProc);
        return symbols.get();
    }

    void Analyze::nullProc(const TreeNode *)
    {
    }

    void Analyze::insert_node(const TreeNode *tree_node)
    {
        switch (tree_node->kind)
        {
        case DIM_K:
            for (const auto &i : tree_node->child)
            {
                symbols.insert(i->attr.name, DIM_V, i->type, i->lineno, to_int(i->attr.value), to_int(i->attr.value_2));
            }

            break;
        default:
            break;
        }
    }

    void Analyze::traverse(const TreeNode *tree_node, void (Analyze::*pre_proc)(const TreeNode *), void (Analyze::*post_proc)(const TreeNode *))
    {
        (this->*pre_proc)(tree_node);

        for (const auto &i : tree_node->child)
        {
            traverse(i, pre_proc, post_proc);
        }

        (this->*post_proc)(tree_node);
    }
}
