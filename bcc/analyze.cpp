#include "analyze.h"
#include "treenode.h"
#include <cstdlib>

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

    void Analyze::insertNode(TreeNode * treeNode) {
        vector<TreeNode *>::iterator i;

        switch (treeNode->nodekind) {
            case DimK:
                for (i = treeNode->child.begin(); i != treeNode->child.end(); i++) {
                    symtab->insert((*i)->attr.name.c_str(), DimV, (*i)->type, (*i)->lineno, atoi((*i)->attr.val.c_str()), atoi((*i)->attr.val2.c_str()));
                }
                break;
            default:
                break;
        }
    }

    void Analyze::traverse(TreeNode * treeNode, void (Analyze::* preProc)(TreeNode *), void (Analyze::* postProc)(TreeNode *)) {
        vector<TreeNode *>::iterator i;
        if (treeNode) {
            (this->*preProc)(treeNode);

            for (i = treeNode->child.begin(); i != treeNode->child.end(); i++) {
                traverse(*i, preProc, postProc);
            }
            (this->*postProc)(treeNode);
            traverse(treeNode->sibling, preProc, postProc);
        }
    }
}
