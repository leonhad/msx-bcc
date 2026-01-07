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
        TokenType current_token;
        Scan scan;

      public:
        explicit Parser(const std::string& file_input);
        ~Parser() = default;

        TreeNode *parse();

      private:
        TreeNode *line_sequence();
        TreeNode *dim_sequence();
        TreeNode *declare_sequence();
        TreeNode *end_sequence();
        TreeNode *print_sequence();
        TreeNode *assign_sequence();
        TreeNode *exp_sequence();
        TreeNode *stmt_sequence();
        TreeNode *statement();
        void match(TokenType expected);
    };

} // namespace bc
