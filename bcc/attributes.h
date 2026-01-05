#pragma once

#include "definitions.h"
#include <string>

namespace bc
{
    class Attributes
    {
      public:
        definitions::TokenType op;
        std::string val;
        std::string val2;
        std::string name;

        Attributes();
        ~Attributes() = default;
    };
} // namespace bc
