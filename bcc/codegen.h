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
        std::string filein;
        std::string currentLine;
        std::ofstream *fileout;
        unsigned int locals;
        unsigned int scope;

      public:
        CodeGen(std::string filein, std::string fileout);
        ~CodeGen();
        void generate(TreeNode *syntaxTree, std::vector<SYMBOL_TABLE> symtabs);

      private:
        void emitFile(const char *file);
        void emitVersion();
        void emitBreakline();
        void emitAlign(int align);
        void emitComment(const char *comment);
        void emitSection(definitions::SectionType section);
        void emitInitMethod(const char *name, unsigned int line);
        void generateVars(std::vector<SYMBOL_TABLE> symtabs);
        void generateLine(TreeNode *tree);
        void generateDim(TreeNode *tree);
        void generateDeclare(TreeNode *tree);
        void generatePrint(TreeNode *tree);
    };
} // namespace bc
