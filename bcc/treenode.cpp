#include "treenode.h"

namespace bc
{
    TreeNode::TreeNode(definitions::NodeKind kind, unsigned int lineno)
    {
        sibling = NULL;
        nodekind = kind;
        this->lineno = lineno;
    }
    
    TreeNode::~TreeNode()
    {
        std::vector<TreeNode*>::iterator i;
        for (i = child.begin(); i != child.end(); i++) {
            delete *i;
        }
    }
}
