#include "treenode.h"

namespace bc
{
    TreeNode::TreeNode(NodeKind kind, unsigned int lineno)
    {
        sibling = NULL;
        nodekind = kind;
        this->lineno = lineno;
    }
    
    TreeNode::~TreeNode()
    {
        vector<TreeNode*>::iterator i;
        for (i = child.begin(); i != child.end(); i++) {
            delete *i;
        }
    }
}
