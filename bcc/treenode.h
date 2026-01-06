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
        explicit TreeNode(definitions::NodeKind kind, unsigned int lineno);
        ~TreeNode() = default;

        void addChild(const TreeNode &child);

        const unsigned int lineno;
        definitions::NodeKind kind;

        std::vector<TreeNode> child;
        Attributes attr;
        definitions::ExpType type;
    };
}
