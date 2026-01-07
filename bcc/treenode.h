#pragma once

#include "attributes.h"
#include "definitions.h"
#include <vector>

namespace bc
{
    class TreeNode
    {
      public:
        explicit TreeNode(NodeKind kind, unsigned int line_number);
        ~TreeNode();

        void add_child(TreeNode *node);

        const unsigned int lineno;
        NodeKind kind;

        std::vector<TreeNode *> child;
        Attributes attr;
        ExpressionType type;
    };
}
