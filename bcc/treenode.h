#pragma once

#include "attributes.h"
#include "definitions.h"

#include <memory>
#include <vector>

namespace bc
{

    class TreeNode
    {
      public:
        explicit TreeNode(definitions::NodeKind kind, unsigned int line_number);
        ~TreeNode();

        void add_child(TreeNode *node);

        const unsigned int lineno;
        definitions::NodeKind kind;

        std::vector<TreeNode *> child;
        Attributes attr;
        definitions::ExpType type;
    };
}
