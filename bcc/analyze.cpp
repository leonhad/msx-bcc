#include "analyze.h"
#include "treenode.h"
#include <cstdlib>

using namespace std;
using namespace definitions;

namespace bc {

    Analyze::Analyze() {
        symtab = new Symtab;
    }

    Analyze::~Analyze() {
        if (symtab) delete symtab;
    }

    vector<SYMTAB *> Analyze::buildSymtab(TreeNode * syntaxTree) {
        traverse(syntaxTree, &Analyze::insertNode, &Analyze::nullProc);
        return symtab->getSymtab();
    }

    void Analyze::nullProc(TreeNode * treeNode) {

    }

    void Analyze::insertNode(TreeNode * treeNode) const {
        switch (treeNode->nodekind) {
            case DimK:
                for (const auto & i : treeNode->child) {
                    symtab->insert(i->attr.name.c_str(), DimV, i->type, i->lineno, atoi(i->attr.val.c_str()), atoi(i->attr.val2.c_str()));
                }
                break;
            default:
                break;
        }
    }

    void Analyze::traverse(TreeNode * treeNode, void (Analyze::* preProc)(TreeNode *) const, void (Analyze::* postProc)(TreeNode *)) {
        if (treeNode) {
            (this->*preProc)(treeNode);

            for (auto i = treeNode->child.begin(); i != treeNode->child.end(); ++i) {
                traverse(*i, preProc, postProc);
            }
            (this->*postProc)(treeNode);
            traverse(treeNode->sibling, preProc, postProc);
        }
    }
}
