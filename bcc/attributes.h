#pragma once

#include "definitions.h"
#include <string>

namespace bc
{
    class Attributes
    {
      public:
        definitions::TokenType operation;
        std::string value;
        std::string value_2;
        std::string name;

        Attributes();
        ~Attributes() = default;
    };
} // namespace bc
