#include "treenode.h"

namespace bc
{
    TreeNode::TreeNode(const definitions::NodeKind kind, const unsigned int lineno) : lineno{lineno}, kind{kind}, type{definitions::ExpType::Float}
    {
    }

    TreeNode::~TreeNode()
    {
        for (const auto &i : child)
        {
            delete i;
        }
    }

    void TreeNode::addChild(TreeNode *node)
    {
        this->child.push_back(node);
    }
}
