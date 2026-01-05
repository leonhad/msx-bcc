#pragma once

#include "codegen.h"
#include "parser.h"
#include <string>

namespace bc
{
    class Compiler
    {
        Parser *parser;
        TreeNode *syntaxTree;
        CodeGen *codegen;

        std::string fileout;
        std::string filein;
        std::string fileAssembly;

      public:
        Compiler(const char *filein, const char *fileout);
        ~Compiler();
        void run();

      private:
        void compile() const;
    };

}
