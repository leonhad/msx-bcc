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
        std::vector<SYMBOL_TABLE> symbols;

        unsigned int locals;
        unsigned int scope;

      public:
        explicit CodeGen(const std::string &output);
        ~CodeGen();
        void generate(const TreeNode *syntax_tree, const std::vector<SYMBOL_TABLE> &table);

      private:
        void emit_file(const char *file);
        void emit_version();
        void emit_break_line();
        void emit_align(int align);
        void emit_comment(const char *comment);
        void emit_section(SectionType section);
        void emit_init_method(const char *name);
        void generate_vars();
        void generate_line(const TreeNode *tree);
        void generate_dim(const TreeNode *tree);
        void generate_assign(const TreeNode *tree);
        void generate_declare(const TreeNode *tree);
        void generate_print(const TreeNode *tree);
    };
}
