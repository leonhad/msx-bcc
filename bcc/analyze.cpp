#include "analyze.h"
#include "treenode.h"

namespace bc
{
    unsigned int toInt(const std::string &str)
    {
        unsigned int ret = 0;
        try
        {
            if (!str.empty())
            {
                ret = std::stoi(str);
            }
        }
        catch (std::exception &)
        {
        }

        return ret;
    }

    std::vector<SYMBOL_TABLE> Analyze::buildSymbolTable(const TreeNode *syntaxTree)
    {
        traverse(syntaxTree, &Analyze::insertNode, &Analyze::nullProc);
        return symtab.get();
    }

    void Analyze::nullProc(const TreeNode *)
    {
    }

    void Analyze::insertNode(const TreeNode *treeNode)
    {
        switch (treeNode->kind)
        {
        case definitions::DimK:
            for (const auto &i : treeNode->child)
            {
                symtab.insert(i->attr.name, DimV, i->type, i->lineno, toInt(i->attr.val), toInt(i->attr.val2));
            }

            break;
        default:
            break;
        }
    }

    void Analyze::traverse(const TreeNode *treeNode, void (Analyze::*preProc)(const TreeNode *), void (Analyze::*postProc)(const TreeNode *))
    {
        (this->*preProc)(treeNode);

        for (const auto &i : treeNode->child)
        {
            traverse(i, preProc, postProc);
        }

        (this->*postProc)(treeNode);
    }
}
