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
        // FIXME change logic to search for usage
        switch (tree_node->kind)
        {
        case DIM_K:
            // FIXME change logic to search for declaration
            for (const auto &i : tree_node->child)
            {
                symbols.insert(i->attr.name, DIM_V, i->type, i->lineno, to_int(i->attr.value), to_int(i->attr.value_2));
            }

            break;
        case ASSIGN_K:
            // FIXME change logic to search for type usage (variable or dim)
            symbols.insert(tree_node->attr.name, VARIABLE_V, tree_node->type, tree_node->lineno, to_int(tree_node->attr.value), to_int(tree_node->attr.value_2));
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
