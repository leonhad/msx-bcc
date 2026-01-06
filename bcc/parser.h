#pragma once

#include "scan.h"
#include "treenode.h"

#include <string>

namespace bc
{

    class Parser
    {
        int line;
        int program_line;
        /* holds current token */
        definitions::TokenType token;
        Scan *scan;

      public:
        explicit Parser(std::string filein);
        ~Parser();
        TreeNode parse();

      private:
        TreeNode line_sequence();
        TreeNode dim_sequence();
        TreeNode declare_sequence();
        TreeNode end_sequence();
        TreeNode print_sequence();
        TreeNode assign_sequence();
        TreeNode exp_sequence();
        TreeNode stmt_sequence();
        TreeNode statement();
        void match(definitions::TokenType expected);
    };

} // namespace bc
