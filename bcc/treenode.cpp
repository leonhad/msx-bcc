#include "treenode.h"

namespace bc
{
    TreeNode::TreeNode(const definitions::NodeKind kind, const unsigned int lineno) : lineno{lineno}, kind{kind}, type{definitions::ExpType::Float}
    {
    }

    void TreeNode::addChild(const TreeNode &child)
    {
        this->child.push_back(child);
    }

}