#include "analyze.h"
#include "treenode.h"
#include <cstdlib>

using namespace std;
using namespace definitions;

namespace bc
{
    vector<SYMBOL_TABLE> Analyze::buildSymbolTable(const TreeNode &syntaxTree)
    {
        traverse(syntaxTree, &Analyze::insertNode, &Analyze::nullProc);
        return symtab.get();
    }

    void Analyze::nullProc(const TreeNode &treeNode)
    {
    }

    void Analyze::insertNode(const TreeNode &treeNode)
    {
        switch (treeNode.kind)
        {
        case DimK:
            for (const auto &i : treeNode.child)
            {
                symtab.insert(i.attr.name, DimV, i.type, i.lineno, atoi(i.attr.val.c_str()), atoi(i.attr.val2.c_str()));
            }
            break;
        default:
            break;
        }
    }

    void Analyze::traverse(const TreeNode &treeNode, void (Analyze::*preProc)(const TreeNode &), void (Analyze::*postProc)(const TreeNode &))
    {
        (this->*preProc)(treeNode);

        for (const auto &i : treeNode.child)
        {
            traverse(i, preProc, postProc);
        }
        (this->*postProc)(treeNode);
    }
}
