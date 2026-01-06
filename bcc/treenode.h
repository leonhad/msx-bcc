#pragma once

#include "attributes.h"
#include "definitions.h"
#include <vector>

namespace bc
{
    class TreeNode
    {
      public:
        TreeNode(definitions::NodeKind kind, unsigned int lineno);
        ~TreeNode();

        std::vector<TreeNode *> child;
        TreeNode *sibling;
        unsigned int lineno;
        definitions::NodeKind kind;

        Attributes attr;
        definitions::ExpType type;
    };

}
