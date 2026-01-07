#pragma once

#include "definitions.h"
#include "symbol_table.h"
#include "treenode.h"
#include <fstream>
#include <string>

namespace bc
{
    class CodeGen
    {
        std::string current_line;
        std::ofstream output;

        unsigned int locals;
        unsigned int scope;

      public:
        explicit CodeGen(const std::string &output);
        ~CodeGen();
        void generate(const TreeNode *syntax_tree, const std::vector<SYMBOL_TABLE> &symbols);

      private:
        void emit_file(const char *file);
        void emit_version();
        void emit_break_line();
        void emit_align(int align);
        void emit_comment(const char *comment);
        void emit_section(SectionType section);
        void emit_init_method(const char *name, unsigned int line);
        void generate_vars(const std::vector<SYMBOL_TABLE> &symbols);
        void generate_line(TreeNode *tree);
        void generate_dim(TreeNode *tree);
        void generate_declare(const TreeNode *tree);
        void generate_print(const TreeNode *tree);
    };
}
