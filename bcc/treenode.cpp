#include "treenode.h"

namespace bc
{
    TreeNode::TreeNode(const definitions::NodeKind kind, const unsigned int line_number) : lineno{line_number}, kind{kind}, type{definitions::ExpressionType::NUMERIC_T}
    {
    }

    TreeNode::~TreeNode()
    {
        for (const auto &i : child)
        {
            delete i;
        }
    }

    void TreeNode::add_child(TreeNode *node)
    {
        this->child.push_back(node);
    }
}
