#include "analyze.h"
#include "treenode.h"
#include <cstdlib>

using namespace std;
using namespace definitions;

namespace bc
{
    vector<SYMBOL_TABLE> Analyze::buildSymbolTable(TreeNode *syntaxTree)
    {
        traverse(syntaxTree, &Analyze::insertNode, &Analyze::nullProc);
        return symtab.getSymtab();
    }

    void Analyze::nullProc(TreeNode *treeNode)
    {
    }

    void Analyze::insertNode(TreeNode *treeNode)
    {
        switch (treeNode->nodekind)
        {
        case DimK:
            for (const auto &i : treeNode->child)
            {
                symtab.insert(i->attr.name.c_str(), DimV, i->type, i->lineno, atoi(i->attr.val.c_str()), atoi(i->attr.val2.c_str()));
            }
            break;
        default:
            break;
        }
    }

    void Analyze::traverse(TreeNode *treeNode, void (Analyze::*preProc)(TreeNode *), void (Analyze::*postProc)(TreeNode *))
    {
        if (treeNode)
        {
            (this->*preProc)(treeNode);

            for (const auto & i : treeNode->child)
            {
                traverse(i, preProc, postProc);
            }
            (this->*postProc)(treeNode);
            traverse(treeNode->sibling, preProc, postProc);
        }
    }
}
