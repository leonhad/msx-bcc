#pragma once

#include "parser.h"
#include <string>

namespace bc
{
    class Compiler
    {
        std::string output;
        std::string input;
        std::string assembly;

      public:
        Compiler(const char *input, const char *output);
        ~Compiler() = default;

        void run() const;

      private:
        void compile() const;
    };

}
