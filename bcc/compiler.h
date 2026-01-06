#pragma once

#include "codegen.h"
#include "parser.h"
#include <string>

namespace bc
{
    class Compiler
    {
        std::string fileout;
        std::string filein;
        std::string fileAssembly;

      public:
        Compiler(const char *filein, const char *fileout);
        ~Compiler() = default;

        void run() const;

      private:
        void compile() const;
    };

}
