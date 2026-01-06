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
        std::string currentLine;
        std::ofstream *outputFile;

        unsigned int locals;
        unsigned int scope;

      public:
        CodeGen(const std::string &output);
        ~CodeGen();
        void generate(TreeNode *syntaxTree, const std::vector<SYMBOL_TABLE> &symtabs);

      private:
        void emitFile(const char *file);
        void emitVersion();
        void emitBreakline();
        void emitAlign(int align) const;
        void emitComment(const char *comment) const;
        void emitSection(definitions::SectionType section) const;
        void emitInitMethod(const char *name, unsigned int line) const;
        void generateVars(const std::vector<SYMBOL_TABLE> &symtabs) const;
        void generateLine(TreeNode *tree);
        void generateDim(TreeNode *tree);
        void generateDeclare(TreeNode *tree);
        void generatePrint(TreeNode *tree);
    };
}
