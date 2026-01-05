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

      public:
        Compiler(std::string filein, std::string fileout);
        ~Compiler();
        void run();
    };

} // namespace bc
